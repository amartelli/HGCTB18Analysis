#ifndef RecoParticleFlow_PFClusterProducer_ComputeHGCALTime_h
#define RecoParticleFlow_PFClusterProducer_ComputeHGCALTime_h

// user include files
#include <algorithm>
#include <cmath>
#include <vector>
#include "TF1.h"


// functions to select the hits to compute the time of a given cluster
// start with the only hits with timing information
// average among the hits contained in the chosen time interval

// N.B. time is corrected wrt vtx-calorimeter distance
// with straight line and light speed hypothesis
// for charged tracks or heavy particles (longer track length or beta < 1)
// need to correct the offset at analysis level


inline std::vector<size_t> decrease_sorted_indices(const std::vector<float>& v)
{
  // initialize original index locations
  std::vector<size_t> idx(v.size());
  for (size_t i = 0; i != idx.size(); ++i) idx[i] = i;

  // sort indices based on comparing values in v (decreasing order)
  std::sort(idx.begin(), idx.end(),
	    [&v](size_t i1, size_t i2) {return v[i1] < v[i2];} );

  return idx;
}



namespace hgcaltime {

  //time resolution vs energy parametrization
  Double_t timeResolution(Double_t *x, Double_t *par) {

    Double_t funcVal = pow(par[0]/x[0], 2) + pow(par[1], 2);
    return sqrt(funcVal);
  }

  //time-interval based on that ~210ps wide and with the highest number of hits
  float fixSizeHighestDensity(std::vector<float>& time,
			      std::vector<float> weight = std::vector<float>(),
                              float deltaT = 0.210 /*time window in ns*/,
                              float timeWidthBy = 0.5) {


    if(weight.size() == 0) weight.resize(time.size(), 1.);

    std::vector<float> t (time.size(), 0.);
    std::vector<float> w (time.size(), 0.);
    std::vector<size_t> sortedIndex = decrease_sorted_indices(time);
    for (std::size_t i=0; i<sortedIndex.size(); ++i) {
      t[i] = time[sortedIndex[i]];
      w[i] = weight[sortedIndex[i]];
    }

    int max_elements = 0;
    int start_el = 0;
    int end_el = 0;
    float timeW = 0.f;
    float tolerance = 0.05f;

    for (auto start = t.begin(); start != t.end(); ++start) {
      const auto startRef = *start;
      int c = count_if(start, t.end(), [&](float el) { return el - startRef <= deltaT + tolerance; });
      if (c > max_elements) {
        max_elements = c;
        auto last_el = find_if_not(start, t.end(), [&](float el) { return el - startRef <= deltaT + tolerance; });
        auto val = *(--last_el);
        if (std::abs(deltaT - (val - startRef)) < tolerance) {
          tolerance = std::abs(deltaT - (val - startRef));
        }
        start_el = distance(t.begin(), start);
        end_el = distance(t.begin(), last_el);
        timeW = val - startRef;
      }
    }

    // further adjust time width around the chosen one based on the hits density
    // proved to improve the resolution: get as many hits as possible provided they are close in time

    float HalfTimeDiff = timeW * timeWidthBy;
    float sum = 0.;
    float num = 0.;
    int totSize = t.size();

    for (int ij = 0; ij <= start_el; ++ij) {
      if (t[ij] > (t[start_el] - HalfTimeDiff)) {
        for (int kl = ij; kl < totSize; ++kl) {
          if (t[kl] < (t[end_el] + HalfTimeDiff)) {
	    sum += t[kl] * w[kl];
	    num += w[kl];
          } else
            break;
        }
        break;
      }
    }

    if (num == 0) return -99.;
    return sum / num;
  }


  float fixSizeHighestDensityResWeig(std::vector<float>& t,
				     std::vector<float>& w,
				     std::string& type,
				     float deltaT = 0.210 /*time window in ns*/,
				     float timeWidthBy = 0.5){


    //range is in GeV units
    TF1* func = new TF1("func", timeResolution, 0.02, 1000., 2);
    if(type == "test"){
      //time is in ns units
      func->SetParameters(1., 0.02);
    }

    std::vector<float> weights;
    weights.resize(t.size());

    for (unsigned int ij = 0; ij < w.size(); ++ij) {
      float energy = w[ij];

      if(energy > func->GetXmax()) weights[ij] = 1./func->GetParameter(1);
      else if(energy < func->GetXmin()) weights[ij] = 1./func->GetParameter(0);
      else weights[ij] = 1./func->Eval(energy);
    }

    return fixSizeHighestDensity(t, weights, deltaT, timeWidthBy);
  }



  //useful for future developments - baseline for 0PU
  /*
  //time-interval based on the smallest one containing a minimum fraction of hits
  // vector with time values of the hit; fraction between 0 and 1; how much furher enlarge the selected time window
  float highestDensityFraction(std::vector<float>& hitTimes, float fractionToKeep=0.68, float timeWidthBy=0.5){
    std::sort(hitTimes.begin(), hitTimes.end());
    int totSize = hitTimes.size();
    int num = 0.;
    float sum = 0.;
    float minTimeDiff = 999.;
    int startTimeBin = 0;
    int totToKeep = int(totSize*fractionToKeep);
    int maxStart = totSize - totToKeep;
    for(int ij=0; ij<maxStart; ++ij){
      float localDiff = fabs(hitTimes[ij] - hitTimes[int(ij+totToKeep)]);
      if(localDiff < minTimeDiff){
      minTimeDiff = localDiff;
      startTimeBin = ij;
      }
    }
    // further adjust time width around the chosen one based on the hits density
    // proved to improve the resolution: get as many hits as possible provided they are close in time
    int startBin = startTimeBin;
    int endBin = startBin+totToKeep;
    float HalfTimeDiff = std::abs(hitTimes[startBin] - hitTimes[endBin]) * timeWidthBy;
    for(int ij=0; ij<startBin; ++ij){
      if(hitTimes[ij] > (hitTimes[startBin] - HalfTimeDiff) ){
      for(int kl=ij; kl<totSize; ++kl){
        if(hitTimes[kl] < (hitTimes[endBin] + HalfTimeDiff) ){
	    sum += hitTimes[kl];
	        ++num;
		  }
		    else  break;
		    }
		    break;
      }
    }
    if(num == 0) return -99.;
    return sum/num;
  }
  */
}  // namespace hgcalsimclustertime

#endif
