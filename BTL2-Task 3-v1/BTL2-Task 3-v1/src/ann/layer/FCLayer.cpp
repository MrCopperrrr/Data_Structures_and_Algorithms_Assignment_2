/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/class.cc to edit this template
 */

/* 
 * File:   FCLayer.cpp
 * Author: ltsach
 * 
 * Created on August 25, 2024, 11:06 AM
 */

#include "layer/FCLayer.h"
#include "ann/functions.h"
#include "sformat/fmt_lib.h"
#include <sstream>
#include <exception>
#include <filesystem> //require C++17
#include "tensor/xtensor_lib.h"
#include <xtensor/xarray.hpp>

namespace fs = std::filesystem;
using namespace std;

FCLayer::FCLayer(int Nin, int Nout, bool use_bias) {
    this->m_nNin = Nin;
    this->m_nNout = Nout;
    this->m_bUse_Bias = use_bias;
    m_sName = "FC_" + to_string(++m_unLayer_idx);
    m_unSample_Counter = 0;
    
    init_weights();

}

FCLayer::FCLayer(string sParams, string filename_w, string filename_b, string sName){
    //update name
    if(trim(sName).size() != 0) this->m_sName = sName;
    else m_sName = "FC_" + to_string(++m_unLayer_idx);
    
    //parse sParams to get Nin, Nout, use-bias
    try{
        //extract Nin, Nout, use-bias from sParams:
        char delimiter=',';
        istringstream param_stream(sParams);
        int nparams[] = {0, 0, 0}; //for: Nin, Nout, use_bias
        string param_slist[] = {"", "", ""}; //for: Nin, Nout, use_bias
        int idx=0;
        while(getline(param_stream, param_slist[idx], delimiter)){
            nparams[idx] = stoi(param_slist[idx]);
            idx++;
            if(idx >= 3) break; //just use the first three elements
        }
        if(idx == 2){
            cout << "use-bias: not specified; to use-bias=true" << endl;
            nparams[2] = 1;
        }
        else if(idx < 2){
            throw std::runtime_error("FC's parameters: must specify at least Nin and Nout");
        }
        //
        this->m_nNin = nparams[0];
        this->m_nNout = nparams[1];
        this->m_bUse_Bias = nparams[2];
        this->m_unSample_Counter = 0;

        
        bool weight_file_invalid = !fs::exists(filename_w);
        bool bias_file_invalid = m_bUse_Bias && !fs::exists(filename_b);
        if(weight_file_invalid){
            //DO INITIALIZATION when files are invalid
            //Weight file is not specified correctly => initialize randomly
            string message = fmt::format("{:s}: not exist; so initialize weights with random numbers", filename_w);
            cout << message << endl;
            
            //initialize
            this->m_aWeights = xt::random::randn<double>({m_nNout, m_nNin});
            this->m_aGrad_W = xt::zeros<double>({m_nNout, m_nNin});
        }
        else{
            //DO LOADING WEIGHTS when the file are valid
            double_tensor W = xt::load_npy<double>(filename_w);
            bool valid = (W.dimension() == 2) && 
                         (W.shape()[0] == m_nNout) &&
                         (W.shape()[1] == m_nNin);
            if(!valid){
                throw std::runtime_error("FC::Weights: shape from data file is not the same with the specification");
            }
            this->m_aWeights = W;
            this->m_aGrad_W = xt::zeros<double>({m_nNout, m_nNin}); //initialize gradW
        }
        if(bias_file_invalid){
            //Bias file is not specified correctly => initialize with 0
            string message = fmt::format("{:s}: not exist; so initialize biases with 0", filename_b);
            cout << message << endl;
           
            //initialize
            this->m_aBias = xt::zeros<double>({m_nNout});
            this->m_aGrad_b = xt::zeros<double>({m_nNout});
        }
        else{
            //DO LOADING BIAS when the file are valid
            if(m_bUse_Bias){
                double_tensor b = xt::load_npy<double>(filename_b);
                bool valid = (b.dimension() == 1) && (b.shape()[0] == m_nNout) ;
                if(!valid)
                    throw std::runtime_error("FC::Bias: shape from data is not the same with the specification");

                //loading
                this->m_aBias = b;
                this->m_aGrad_b = xt::zeros<double>({m_nNout});  //initialize gradW
            }
        }
    }
    catch(exception& e){
        string message = fmt::format(
                            string("\tsParams: \"{:s}\";\r\n") +
                            string("\tfilename_w: \"{:s}\";\r\n") +
                            string("\tfilename_b: \"{:s}\";\r\n") +
                            string("\tsName(layer-name):\"{:s}\""),
                            sParams, filename_w, filename_b, sName); 
        cerr << "In FCLayer:FCLayer(.,.,.,.), with the following info:" << endl;
        cout << message << endl;
        cerr << "-------EXCEPTION: BEGIN-------" << endl;
        cerr << "\t" << e.what() << endl;
        cerr << "-------EXCEPTION: END-------" << endl;
        throw; //re-throw to the caller
    }
}

void FCLayer::init_weights(){
    this->m_aWeights = xt::random::randn<double>({m_nNout, m_nNin});
    this->m_aGrad_W = xt::zeros<double>({m_nNout, m_nNin});
    
    if(m_bUse_Bias){
        //this->m_aBias = xt::random::randn<double>({m_nNout});
        this->m_aBias = xt::zeros<double>({m_nNout});
        this->m_aGrad_b = xt::zeros<double>({m_nNout});
    }
}

FCLayer::FCLayer(const FCLayer& orig) {
    m_sName = "FC_" + to_string(++m_unLayer_idx);
}

FCLayer::~FCLayer() {
}



xt::xarray<double> FCLayer::forward(xt::xarray<double> X) {
    // Kiểm tra chế độ training trước khi cache đầu vào
    if (m_trainable==true) {
        m_aCached_X = X;
    }
    // Tính Y = X * W^T
    xt::xarray<double> Y = xt::linalg::dot(X,xt::transpose( m_aWeights));
    // Kiểm tra chế độ training trước khi cộng thêm bias
    if (m_bUse_Bias) {
        Y += m_aBias;
    }
    return Y;
}

// xt::xarray<double> FCLayer::backward(xt::xarray<double> DY) {
//     // Cập nhật biến m_unSample_Counter
//     m_unSample_Counter += DY.shape()[0];

//     // Lấy kích thước bộ dữ liệu hiện tại
//     int batch_size = DY.shape()[0];

//     // Khởi tạo dW_batch để lưu từng phần tử Δy ⊗ x^T
//     xt::xarray<double> dW_batch = xt::zeros<double>(
//         {DY.shape()[0], m_aWeights.shape()[0], m_aWeights.shape()[1]});

//     // Tính từng phần tử trong dW_batch theo công thức ΔW = Δy ⊗ x^T
//     for (std::size_t i = 0; i < DY.shape()[0]; ++i) {
//         xt::xarray<double> dy_row = xt::view(DY, i, xt::all());
//         xt::xarray<double> x_row = xt::view(m_aCached_X, i, xt::all());
//         xt::view(dW_batch, i, xt::all(), xt::all()) = outer_stack(dy_row, x_row);
//     }

//     // Tính m_aGrad_W bằng cách lấy trung bình dW_batch
//     m_aGrad_W = xt::mean(dW_batch, {0});

//     // Tính Δb = mean(DY, axis=0) nếu sử dụng bias
//     if (m_bUse_Bias) {
//         m_aGrad_b = xt::mean(DY, 0);
//     }

//     // Tính ΔX theo công thức ΔX = ΔY × W^T
//     xt::xarray<double> DX = xt::linalg::dot(DY, m_aWeights);

//     return DX;
// }




xt::xarray<double> FCLayer::backward(xt::xarray<double> DY) {
    m_unSample_Counter += DY.shape()[0];

    xt::xarray<double> out_DY_Cached = outer_stack(DY, m_aCached_X);

    m_aGrad_W = xt::sum(out_DY_Cached, 0);

    if (m_bUse_Bias) {
        m_aGrad_b = xt::sum(DY, 0);
    }

    xt::xarray<double> dX = xt::linalg::dot(DY, m_aWeights);

    return dX;
}



int FCLayer::register_params(IParamGroup* ptr_group){
    ptr_group->register_param("weights", &m_aWeights, &m_aGrad_W);
    int count = 1;
    if(m_bUse_Bias){
        ptr_group->register_param("bias", &m_aBias, &m_aGrad_b);
        count += 1;
    }
    ptr_group->register_sample_count(&m_unSample_Counter);
    return count;
} 

string FCLayer::get_desc(){
    string desc = fmt::format("{:<10s}, {:<15s}: {:<4d}, {:<4d}, {:<4d}",
                    "FC", this->getname(), 
                    this->m_nNin, this->m_nNout, this->m_bUse_Bias);
    return desc;
}
void FCLayer::save(string model_path){
    string filename_w = model_path + "/" + this->getname() + "_W.npy";
    string filename_b = model_path + "/" + this->getname() + "_b.npy";
    
    xt::dump_npy(filename_w, m_aWeights);
    if(m_bUse_Bias){
        xt::dump_npy(filename_b, m_aBias);
    }
}
/*
 * load(string model_path, string layer_name)
 *  + model_path: folder that contains the models' data files: arch.txt and others.
 *  + layer_name: name of FC layer; maybe an empty ("")
 * PRE-CONDITION:
 *  + if param "layer_name" is empty then m_sName in FCLayer MUST BE assigned in advance.
 * POST-CONDITION:
 *  + All members variables of FC; including,
 *       Nin, Nout, use-bias, 
 *       weights and its gradient, 
 *       bias and its graident, 
 *       sample-counter: are assigned according to the data loaded from files.
 *  + weight-file does not exist: exception (const char*)
 *  + bias-file does not exist: use-bias=false;
 * 
 */
void FCLayer::load(string model_path, string layer_name){
    layer_name = trim(layer_name);
    
    string filename_w, filename_b;
    if(layer_name.size() == 0){
        filename_w = model_path + "/" + this->getname() + "_W.npy";
        filename_b = model_path + "/" + this->getname() + "_b.npy";
    }
    else{
        filename_w = model_path + "/" + layer_name + "_W.npy";
        filename_b = model_path + "/" + layer_name + "_b.npy";
    }
    
    try{
        if(fs::exists(filename_w)){
            // DO LOADING from the file
            m_aWeights = xt::load_npy<double>(filename_w);
            m_nNin  = m_aWeights.shape()[1]; 
            m_nNout = m_aWeights.shape()[0]; 
            // Correct the dimensions of m_aGrad_W
            m_aGrad_W = xt::zeros<double>({m_nNout, m_nNin});
        }
        else{
            string message = fmt::format("{:s}: weight-file does not exist.", filename_w);
            throw std::runtime_error(message);
        }
        if(fs::exists(filename_b)){
            m_aBias = xt::load_npy<double>(filename_b);
            // Ensure m_aBias is 1-dimensional
            if(m_aBias.shape().size() > 1){
                m_aBias = xt::reshape_view(m_aBias, {m_nNout});
            }
            if(m_aBias.shape()[0] != m_nNout){
                throw std::runtime_error("Number of values in m_aBias must be the same as Nout and must be 1D.");
            }
            m_aGrad_b = xt::zeros<double>({m_nNout});
            m_bUse_Bias = true;
        }
        else{
            m_bUse_Bias = false;
        }
        
        m_unSample_Counter = 0;
    }
    catch(exception& e){
        cout << e.what() << endl;
        throw; //re-throw to the caller
    }
}
