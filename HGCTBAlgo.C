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

using namespace std;

class HGCTBAlgo {

public :
  virtual ~HGCTBAlgo() {}
  void   Init(std::vector<float>& rechit_energy, std::vector<unsigned int>& rechit_layer,
	      std::vector<short int>& rechit_iu, std::vector<short int>& rechit_iv,
	      std::vector<float>& rechit_x,      std::vector<float>& rechit_y,
	      float cut);
  double SumE();
  double MaxHitE();
  double SumELayer(unsigned int layer);
  double MaxHitELayer(unsigned int layer);
  double Cluster(unsigned int layer, int extend, float cut);    

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

};

void HGCTBAlgo::Init(std::vector<float>& rechit_energy, std::vector<unsigned int>& rechit_layer,
		     std::vector<short int>& rechit_iu, std::vector<short int>& rechit_iv,
		     std::vector<float>& rechit_x, std::vector<float>& rechit_y,
		     float cut){

  float sum_rh_en=0, max_rh_en=0; 
  layer_imax.clear();
  layer_maxhit_uv.clear();  layer_maxhit_en.clear();
  layer_sum_en.clear();     layer_rechit_en.clear();  
  layer_rechit_u.clear();   layer_rechit_v.clear();
  layer_rechit_x.clear();   layer_rechit_y.clear();
  
  unsigned int istart_layer=0;
  for(unsigned int ilayer=1; ilayer <= rechit_layer.back(); ilayer++){
    float sum_rh_en_lay=0, max_rh_en_lay=0;
    unsigned int imax_lay=99999;
    short int    umax_lay=999, vmax_lay=999;
    float        xmax_lay=-9999, ymax_lay=-9999;
    vector<float>     rhs_en_lay; rhs_en_lay.clear();
    vector<short int> rhs_u_lay;  rhs_u_lay.clear();
    vector<short int> rhs_v_lay;  rhs_v_lay.clear();
    vector<float>     rhs_x_lay;  rhs_x_lay.clear();
    vector<float>     rhs_y_lay;  rhs_y_lay.clear();

    //cout << "istart_layer: " << istart_layer << endl;
    for (unsigned int irechit=istart_layer; irechit < rechit_energy.size(); irechit++){
      if (rechit_layer[irechit] != ilayer) break;
      //cout << "irechit: " << irechit << endl;
  
      if(rechit_energy[irechit]>=cut) sum_rh_en+=rechit_energy[irechit];
      if (rechit_energy[irechit] > max_rh_en) {max_rh_en = rechit_energy[irechit];
	imax=irechit;
      }
      
      if(rechit_energy[irechit]>=cut) sum_rh_en_lay+=rechit_energy[irechit];
      if (rechit_energy[irechit] > max_rh_en_lay) {max_rh_en_lay = rechit_energy[irechit];
	imax_lay=irechit; 
	umax_lay=rechit_iu[irechit];  vmax_lay=rechit_iv[irechit];
	xmax_lay=rechit_x[irechit];   ymax_lay=rechit_y[irechit];
      }
      rhs_en_lay.push_back(rechit_energy[irechit]);
      rhs_u_lay.push_back(rechit_iu[irechit]);
      rhs_v_lay.push_back(rechit_iv[irechit]);
      rhs_x_lay.push_back(rechit_x[irechit]);
      rhs_y_lay.push_back(rechit_y[irechit]);
      istart_layer = irechit+1;
    } // rechit loop

    layer_sum_en.push_back(sum_rh_en_lay);
    layer_maxhit_en.push_back(max_rh_en_lay);
    layer_imax.push_back(imax_lay);
    if (debug) cout << "layer imax_layer umax_layer vmax_layer: " 
	 << ilayer << " " << imax_lay << " " << umax_lay << " " << vmax_lay << endl;
    layer_maxhit_uv.push_back( make_pair(umax_lay,vmax_lay) );
    layer_maxhit_xy.push_back( make_pair(xmax_lay,ymax_lay) );
    layer_rechit_en.push_back(rhs_en_lay);
    layer_rechit_u.push_back(rhs_u_lay);
    layer_rechit_v.push_back(rhs_v_lay);
    layer_rechit_x.push_back(rhs_x_lay);
    layer_rechit_y.push_back(rhs_y_lay);


    rhs_en_lay.clear();
    rhs_u_lay.clear();  rhs_v_lay.clear();
    rhs_x_lay.clear();  rhs_y_lay.clear();
  } // layer loop

  sum_en=sum_rh_en; maxhit_en=max_rh_en;
}

// Return sum of all rechits energy with a given threshold cut
double HGCTBAlgo::SumE(){
  return sum_en;
}

// Return maximum rechit cell energy of all rechits 
double HGCTBAlgo::MaxHitE(){
  return maxhit_en;
}

// Return layerwise sum rechit energy with a given threshold cut
double HGCTBAlgo::SumELayer(unsigned int layer){
  float ilay_sum_en=0;
  for (unsigned int ilayer=0; ilayer < layer_sum_en.size(); ilayer++){
    if (debug) cout << "Layer SumE : " << ilayer+1 << " " << layer_sum_en[ilayer] <<endl;
    if (ilayer==layer-1)  ilay_sum_en= layer_sum_en[ilayer]; 
  }
  return ilay_sum_en;
}

// Return layerwise maximum hit cell energy
double HGCTBAlgo::MaxHitELayer(unsigned int layer){
  float ilay_max_en=0;
  for (unsigned int ilayer=0; ilayer < layer_maxhit_en.size(); ilayer++){
    if (debug) cout << "Layer MaxE : " << ilayer+1 << " " << layer_maxhit_en[ilayer] <<endl;
    if (ilayer==layer-1)  ilay_max_en= layer_maxhit_en[ilayer];
  }
  return ilay_max_en;
}

// Make layerwise cluster of cells and return sum energy of 
// the cluster i.e. R1,R7,R19 and so on 
// For R1 extend=0, R7 extend=1 and so on
// Include the cells in the cluster with a given threshold energy cut
double HGCTBAlgo::Cluster(unsigned int layer, int extend, float cut){
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

