// -*- C++ -*-
//
// Package:    ROOT
// Class:      HGCTBAlgo
// 
// Original Author:  Ashim Roy
//         Created:  Tue, 20 Aug 2019 09:44:32 GMT
//

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "ComputeHGCALTime.h"

using namespace std;

float cellRad = 0.563 + 0.001; ///0.001 is the delta
float minE_time = 15; ///15 mips

float speed_light = 29.9792; ///cm/ns


//bool debugL2_ = true;
bool debugL2_ = false;

class HGCTBAlgo {

public :
  virtual ~HGCTBAlgo() {}
  void   Init(std::vector<float>& rechit_energy, std::vector<unsigned int>& rechit_layer,
	      std::vector<short int>& rechit_iu, std::vector<short int>& rechit_iv,
	      std::vector<float>& rechit_x,      std::vector<float>& rechit_y,
	      std::vector<float>& rechit_time_mc, std::vector<float>& rechit_time_mc_firstHit,
	      std::vector<float>& rechit_time_mc_lastHit, std::vector<float>& rechit_z,
	      float cut);
  float SumE();
  float MaxHitE();
  float SumELayer(unsigned int layer);
  float MaxHitELayer(unsigned int layer);
  float Cluster(unsigned int layer, int extend, float cut);    
  vector<float> LayerTimeDiff(unsigned int layer, int extend);
  float EnWeiLayerTime(unsigned int layer, int extend, float &sumE, bool applyTOFCorr);
  float GetTime(unsigned int layer, int extend);
  
private :
  bool  debug=false;  
  float sum_en;
  pair<int,int> maxhit_uv;
  pair<float,float> maxhit_xy; 
  float maxhit_en; unsigned int imax=999999;
  vector< pair<short int,short int> > layer_maxhit_uv;
  vector< pair<float,float> > layer_maxhit_xy;
  vector<float> layer_maxhit_en; vector<unsigned int> layer_imax;
  vector<float> layer_sum_en; 
  vector< vector<float> > layer_rechit_en; 
  vector< vector<short int> > layer_rechit_u; vector< vector<short int> > layer_rechit_v; 
  vector< vector<float> > layer_rechit_x; vector< vector<float> > layer_rechit_y; 
  vector< vector<float> > layer_rechit_time;
  vector< vector<float> > layer_rechit_t; vector< vector<float> > layer_rechit_tfh; 
  vector< vector<float> > layer_rechit_tlh;
  vector< vector<float> > layer_rechit_z;
  
  vector<float> layer_maxhit_z; 
  vector<float> layer_maxhit_t; 
  vector<float> layer_maxhit_tfh;
  vector<float> layer_maxhit_tlh;  

  // std::vector<float> layerRh;
  // std::vector<float> timeRh;
  // std::vector<float> energyRh;
  // std::vector<float> xRh;
  // std::vector<float> yRh;

  float firstlayer_rechit_z = -99999;

};

void HGCTBAlgo::Init(std::vector<float>& rechit_energy, std::vector<unsigned int>& rechit_layer,
		     std::vector<short int>& rechit_iu, std::vector<short int>& rechit_iv,
		     std::vector<float>& rechit_x, std::vector<float>& rechit_y,
		     std::vector<float>& rechit_time_mc, std::vector<float>& rechit_time_mc_firstHit,
		     std::vector<float>& rechit_time_mc_lastHit, std::vector<float>& rechit_z,
		     float cut){

  float sum_rh_en=0, max_rh_en=0; 


  // layerRh.clear();
  // timeRh.clear();
  // energyRh.clear();
  // xRh.clear();
  // yRh.clear();

  layer_maxhit_xy.clear();
  
  layer_imax.clear();
  layer_maxhit_uv.clear();  layer_maxhit_en.clear();

  layer_sum_en.clear();     layer_rechit_en.clear();  
  layer_rechit_u.clear();   layer_rechit_v.clear();
  layer_rechit_x.clear();   layer_rechit_y.clear();
  layer_rechit_time.clear();
  ///SJ
  layer_rechit_t.clear();
  layer_rechit_tfh.clear();
  layer_rechit_tlh.clear();


  ///SJ
  layer_maxhit_t.clear();
  layer_maxhit_tfh.clear();
  layer_maxhit_tlh.clear();

  ///SJ
  layer_rechit_z.clear();
  layer_maxhit_z.clear();

  bool notFilledZ = true;
  
  unsigned int istart_layer=0;

  for(unsigned int ilayer=1; ilayer <= rechit_layer.back(); ilayer++){

    float sum_rh_en_lay=0, max_rh_en_lay=0;
    unsigned int imax_lay=99999;
    short int    umax_lay=999, vmax_lay=999;
    float        xmax_lay=-9999, ymax_lay=-9999;
    float        tmax_lay=-9999, tfhmax_lay=-9999, tlhmax_lay=-9999;
    
    float zmax_lay=-999;

    //float emax_lay = -999;
    
    vector<float>     rhs_en_lay; rhs_en_lay.clear();
    vector<short int> rhs_u_lay;  rhs_u_lay.clear();
    vector<short int> rhs_v_lay;  rhs_v_lay.clear();
    vector<float>     rhs_x_lay;  rhs_x_lay.clear();
    vector<float>     rhs_y_lay;  rhs_y_lay.clear();
    //RA 
    vector<float>     rhs_time_lay;  rhs_time_lay.clear();

    ///SJ
    vector<float>     rhs_t_lay; rhs_t_lay.clear();
    vector<float>     rhs_tfh_lay; rhs_tfh_lay.clear();
    vector<float>     rhs_tlh_lay; rhs_tlh_lay.clear();

    vector<float>     rhs_z_lay; rhs_z_lay.clear();
    
    if(debug) std::cout << "istart_layer: " << istart_layer << std::endl;

    unsigned int totLayerHits = rechit_energy.size();
    if(debug) std::cout << " nHits = " << totLayerHits << std::endl;    
    for (unsigned int irechit=istart_layer; irechit < totLayerHits; irechit++){
      if (rechit_layer[irechit] != ilayer) break;

      if(rechit_energy[irechit]>=cut) sum_rh_en+=rechit_energy[irechit];
      if (rechit_energy[irechit] > max_rh_en) {max_rh_en = rechit_energy[irechit];
	imax=irechit;
      }
      
      if(notFilledZ && ilayer==1){
	firstlayer_rechit_z = rechit_z[irechit]; 
	notFilledZ = false;
      }

      //set to 15MIP
      if(rechit_energy[irechit] < cut) continue;

      float timeHit = rechit_time_mc[irechit];
      if(rechit_time_mc[irechit] < rechit_time_mc_firstHit[irechit]) timeHit = rechit_time_mc_firstHit[irechit];
      float dist3Dhit = sqrt(pow(rechit_x[irechit], 2) + pow(rechit_y[irechit], 2) + pow(rechit_z[irechit], 2));
      float tofHit = dist3Dhit/speed_light;
      float timeOffset = 110; //ns = 33m
      if(debug)  std::cout << " dist3Dhit = " << dist3Dhit << " tof = " << tofHit << " timeHit = " << timeHit 
			   << " timeOffset = " << timeOffset << std::endl;
      timeHit = timeHit - tofHit - timeOffset; 

      if(rechit_energy[irechit]>=cut) sum_rh_en_lay+=rechit_energy[irechit];


      if (rechit_energy[irechit] > max_rh_en_lay) {

	max_rh_en_lay = rechit_energy[irechit];
	imax_lay=irechit; 
	umax_lay=rechit_iu[irechit];  vmax_lay=rechit_iv[irechit];
	xmax_lay=rechit_x[irechit];   ymax_lay=rechit_y[irechit];
	
	
	
	//SJ
	tmax_lay = rechit_time_mc[irechit];
	tfhmax_lay = rechit_time_mc_firstHit[irechit];
	tlhmax_lay = rechit_time_mc_lastHit[irechit];
	
	zmax_lay=rechit_z[irechit]; 
	
      }//for max hit per layer
    
      
      rhs_en_lay.push_back(rechit_energy[irechit]);
      rhs_u_lay.push_back(rechit_iu[irechit]);
      rhs_v_lay.push_back(rechit_iv[irechit]);
      rhs_x_lay.push_back(rechit_x[irechit]);
      rhs_y_lay.push_back(rechit_y[irechit]);
      //RA 
      rhs_time_lay.push_back(timeHit);
      

      //SJ
      rhs_t_lay.push_back(rechit_time_mc[irechit]);
      rhs_tfh_lay.push_back(rechit_time_mc_firstHit[irechit]);
      rhs_tlh_lay.push_back(rechit_time_mc_lastHit[irechit]);

      rhs_z_lay.push_back(rechit_z[irechit]);      
      

      istart_layer = irechit+1;      

    } // rechit loop

    if(debug) std::cout << "========== loop over recHits ==========================" << std::endl;



    layer_sum_en.push_back(sum_rh_en_lay);
    layer_maxhit_en.push_back(max_rh_en_lay);
    layer_imax.push_back(imax_lay);
    
    if (debug) std::cout << "layer imax_layer umax_layer vmax_layer: " 
			 << ilayer << " " << imax_lay << " " << umax_lay << " " << vmax_lay << std::endl;
    layer_maxhit_uv.push_back( make_pair(umax_lay,vmax_lay) );
    layer_maxhit_xy.push_back( make_pair(xmax_lay,ymax_lay) );
    ///SJ
    layer_maxhit_t.push_back(tmax_lay);
    layer_maxhit_tfh.push_back(tfhmax_lay);
    layer_maxhit_tlh.push_back(tlhmax_lay);

    layer_maxhit_z.push_back(zmax_lay);

    layer_rechit_en.push_back(rhs_en_lay);
    layer_rechit_u.push_back(rhs_u_lay);
    layer_rechit_v.push_back(rhs_v_lay);
    layer_rechit_x.push_back(rhs_x_lay);
    layer_rechit_y.push_back(rhs_y_lay);
    layer_rechit_time.push_back(rhs_time_lay);
    layer_rechit_z.push_back(rhs_z_lay);

    ///SJ
    layer_rechit_t.push_back(rhs_t_lay);
    layer_rechit_tfh.push_back(rhs_tfh_lay);
    layer_rechit_tlh.push_back(rhs_tlh_lay);

    rhs_en_lay.clear();
    rhs_u_lay.clear();  rhs_v_lay.clear();
    rhs_x_lay.clear();  rhs_y_lay.clear();
    //RA
    rhs_time_lay.clear();

    rhs_t_lay.clear();  rhs_tfh_lay.clear(); rhs_tlh_lay.clear();
    
    rhs_z_lay.clear();
    
  } // layer loop

  sum_en=sum_rh_en; maxhit_en=max_rh_en;

  if(debug) std::cout << " fine main loop " << std::endl;
}

// Return sum of all rechits energy with a given threshold cut
float HGCTBAlgo::SumE(){
  return sum_en;
}

// Return maximum rechit cell energy of all rechits 
float HGCTBAlgo::MaxHitE(){
  return maxhit_en;
}

// Return layerwise sum rechit energy with a given threshold cut
float HGCTBAlgo::SumELayer(unsigned int layer){
  float ilay_sum_en=0;
  if (debug) cout << "Layer SumE : " << layer << " " << layer_sum_en[layer-1] <<endl;
  ilay_sum_en= layer_sum_en[layer-1]; 
  
  return ilay_sum_en;
}

// Return layerwise maximum hit cell energy
float HGCTBAlgo::MaxHitELayer(unsigned int layer){
  float ilay_max_en=0;
  if (debug) cout << "Layer MaxE : " << layer << " " << layer_maxhit_en[layer-1] <<endl;
  ilay_max_en= layer_maxhit_en[layer-1];
  return ilay_max_en;
}

// Make layerwise cluster of cells and return sum energy of 
// the cluster i.e. R1,R7,R19 and so on 
// For R1 extend=0, R7 extend=1 and so on
// Include the cells in the cluster with a given threshold energy cut
float HGCTBAlgo::Cluster(unsigned int layer, int extend, float cut){
  vector< pair<int,int> > uv0; uv0.clear();
  for (int iu=-extend;iu<=extend;iu++){
    for (int iv=-extend;iv<=extend;iv++){
      if ( std::abs(iu+iv)>= extend+1 )	continue;
      //      cout << iu << ":" << iv << endl;
      uv0.push_back( make_pair(iu,iv) ); 
    }
  }  

  int u=0,v=0; float clusterE=0;
  u=layer_maxhit_uv[layer-1].first, v=layer_maxhit_uv[layer-1].second;
  if (debug) cout << "MaxHit iu,iv :" <<u << "," << v << endl;
  for (unsigned int i=0;i<uv0.size();i++){
    int nu= u+uv0[i].first;
    int nv= v+uv0[i].second;
    //cout << nu << ":" << nv << endl;
    for(unsigned int j=0; j<layer_rechit_en[layer-1].size(); j++){
      if(layer_rechit_u[layer-1][j]==nu && layer_rechit_v[layer-1][j]==nv 
	 && layer_rechit_en[layer-1][j]>=cut) clusterE+=layer_rechit_en[layer-1][j];  
    }
  }
  return clusterE;
}




///SJ
vector<float> HGCTBAlgo::LayerTimeDiff(unsigned int layer, int extend){


  vector<float> timeDiff;
  
  float maxX = layer_maxhit_xy[layer-1].first;
  float maxY = layer_maxhit_xy[layer-1].second;
  float maxE = layer_maxhit_en[layer-1];
  float maxT = layer_maxhit_t[layer-1];
  float maxTfh = layer_maxhit_tfh[layer-1];
  float maxTlh = layer_maxhit_tlh[layer-1];
  
  //useHEEPIso_ ? cand->dr03TkSumPtHEEP() : cand->dr03TkSumPt()

  float maxTOA = (maxT > maxTfh) ? maxT : maxTfh;

  
  for(unsigned int j=0; j<layer_rechit_en[layer-1].size(); j++){ 

    float x = layer_rechit_x[layer-1][j];
    float y = layer_rechit_y[layer-1][j];
    float en = layer_rechit_en[layer-1][j];
    float time = layer_rechit_t[layer-1][j];
    float timeFH = layer_rechit_tfh[layer-1][j];
    float timeLH = layer_rechit_tlh[layer-1][j];

    float rad = sqrt( pow(x-maxX, 2) + pow(y-maxY, 2) );
    
    if( (fabs(x-maxX)<0.001)  && (fabs(y-maxY)<0.001) && (fabs(maxE-en)<0.001) ){ 

      //std::cout<<"rejecting hte cell itself from the calculation"<<std::endl;
      continue; //dont iinclude the max cell itself
    }

    if(en < minE_time) continue;
    if(rad > (2*extend+1)*cellRad ) continue;


    float rhTOA = (time > timeFH) ? time : timeFH;
    
    float timediff = rhTOA - maxTOA;

    /*
    if(timediff == 0){


      cout<<"timeDiff is 0!!! maxCell X and Y, other cell X and Y : "<<maxX<<" "<<maxY<<" "<<x<<" "<<y<<endl;
      cout<<"j hit "<<j<<endl;
      cout<<"Layer(-1) is "<<layer-1<<endl;
      cout<<"Time of max : time of RH "<<maxTOA<< " "<<rhTOA<<endl;
      
      cout<<"TimeFH of max : timeFH of RH "<<maxTfh<< " "<<timeFH<<endl;

      cout<<"Time15 of max : time15 of RH "<<maxT<< " "<<time<<endl;

      cout<<"Energy of max : energy of RH "<<maxE<<" "<<en<<endl;

      cout<<"number of this hits in this layer above NO mip  "<<layer_rechit_en[layer-1].size()<<endl;
    }
    */
    
    timeDiff.push_back(timediff);



  }//for(unsigned int j=0; j<layer_rechit_en[layer-1].size(); j++)


  
  return timeDiff;
}//float HGCTBAlgo::ClusterTime(unsigned int layer, int extend, float cut)


float HGCTBAlgo::EnWeiLayerTime(unsigned int layer, int extend, float &sumE, bool applyTOFCorr){


  float layerTime = 0;
  //  float sumE = 0;


  if(firstlayer_rechit_z < 0) {
    std::cout << "WARNING!!!! did not find firstlayer_rechit_z, pls check hte code. Stopping here" << std::endl;
    exit(1);
  }
  
  float maxX = layer_maxhit_xy[layer-1].first;
  float maxY = layer_maxhit_xy[layer-1].second;
  float maxE = layer_maxhit_en[layer-1];
  float maxT = layer_maxhit_t[layer-1];
  float maxTfh = layer_maxhit_tfh[layer-1];
  float maxTlh = layer_maxhit_tlh[layer-1];
  
  //useHEEPIso_ ? cand->dr03TkSumPtHEEP() : cand->dr03TkSumPt()

  float maxTOA = (maxT > maxTfh) ? maxT : maxTfh;

  
  for(unsigned int j=0; j<layer_rechit_en[layer-1].size(); j++){ 

    float x = layer_rechit_x[layer-1][j];
    float y = layer_rechit_y[layer-1][j];
    float en = layer_rechit_en[layer-1][j];
    float time = layer_rechit_t[layer-1][j];
    float timeFH = layer_rechit_tfh[layer-1][j];
    float timeLH = layer_rechit_tlh[layer-1][j];

    float rad = sqrt( pow(x-maxX, 2) + pow(y-maxY, 2) );


    if(en < minE_time) continue;
    if(rad > (2*extend+1)*cellRad ) continue;
    
    
    float rhTOA = (time > timeFH) ? time : timeFH;

    if(debugL2_){
      cout<<""<<endl;
      cout<<"rechit # "<<j<<endl;
    }

    if(applyTOFCorr && (layer-1)!=0){
      
      if(debugL2_){
	cout<<"Layer # : "<<(layer-1)<<std::endl;
	cout<<"This layers Z "<<layer_rechit_z[layer-1][j]<<endl;
	cout<<"First layer Z "<<firstlayer_rechit_z<<endl;
      }
      
      float ToF = ( layer_rechit_z[layer-1][j] - firstlayer_rechit_z)/speed_light;
      rhTOA = rhTOA - ToF;

      if(debugL2_) cout<<"ToF : corrected rhTOA "<<ToF<<" "<<rhTOA<<endl;
    }
     
    
    layerTime += en*rhTOA;
    sumE += en;
    
    
  }//for(unsigned int j=0; j<layer_rechit_en[layer-1].size(); j++)


  
  if(sumE!=0) layerTime = layerTime/sumE;


  return layerTime;
}//float HGCTBAlgo::ClusterTime(unsigned int layer, int extend, float cut)




// energy weighted 
float HGCTBAlgo::GetTime(unsigned int layer, int extend){
  if(debug) std::cout << " hello in GetTime " << std::endl;

  float maxX;
  float maxY;
  float maxE = 0.;

  unsigned int startLayer = layer;
  unsigned int endLayer = layer+1;
  if(layer == -1){
    startLayer = 1;
    endLayer = 30;
  }

  if(debug)  std::cout << " startLayer = " << startLayer << " endLayer = " << endLayer << std::endl;

  for(unsigned int ij = startLayer; ij<endLayer; ++ij){

    auto size = layer_rechit_en[ij-1].size();
    if(debug) std::cout << " size = " << size << std::endl;
    for(auto iR=0; iR<size; ++iR){
      float en = layer_rechit_en[ij-1][iR];

      if(en > maxE){
	maxX = layer_rechit_x[ij-1][iR];
	maxY = layer_rechit_y[ij-1][iR];
	maxE = en;
      }
    }
  }

  if(debug) std::cout << " >>> maxX = " << maxX << " maxY = " << maxY << " maxE = " << maxE << std::endl;

  std::vector<float> times;
  std::vector<float> energies;
  for(unsigned int ij = startLayer; ij<endLayer; ++ij){

    auto size = layer_rechit_en[ij-1].size();
    for(auto iR=0; iR<size; ++iR){
      float x = layer_rechit_x[ij-1][iR];
      float y = layer_rechit_y[ij-1][iR];

      float rad = sqrt( pow(x-maxX, 2) + pow(y-maxY, 2) );
      if(rad > (2*extend+1)*cellRad ) continue;

      float en = layer_rechit_en[ij-1][iR];
      float time = layer_rechit_time[ij-1][iR];
      times.push_back(time);
      energies.push_back(en);
    }
  }

  if(debug) std::cout << " in getTime size = " << times.size()  << std::endl;
  
  if(times.size() >= 3){
    float averageTime = hgcaltime::fixSizeHighestDensity(times, energies);
    return(averageTime);
  }
  else return -99.;
}

