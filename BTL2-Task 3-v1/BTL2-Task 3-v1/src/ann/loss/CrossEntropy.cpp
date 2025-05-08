/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt
 * to change this license Click
 * nbfs://nbhost/SystemFileSystem/Templates/cppFiles/class.cc to edit this
 * template
 */

/*
 * File:   CrossEntropy.cpp
 * Author: ltsach
 *
 * Created on August 25, 2024, 2:47 PM
 */

#include "loss/CrossEntropy.h"

#include "ann/functions.h"

CrossEntropy::CrossEntropy(LossReduction reduction) : ILossLayer(reduction) {}

CrossEntropy::CrossEntropy(const CrossEntropy& orig) : ILossLayer(orig) {}

CrossEntropy::~CrossEntropy() {}

double CrossEntropy::forward(xt::xarray<double> X, xt::xarray<double> t) {
    m_aCached_Ypred = X;
    m_aYtarget = t;
    
    bool mean_reduced = (m_eReduction == LossReduction::REDUCE_MEAN);
    
    return cross_entropy(X, t, mean_reduced);
}

xt::xarray<double> CrossEntropy::backward() {
    const double EPSILON = 1e-7;
    
    xt::xarray<double> grad = -m_aYtarget / (m_aCached_Ypred + EPSILON);

    // chia trung bình nếu cần
    if (m_eReduction == LossReduction::REDUCE_MEAN) {
        int nsamples = m_aCached_Ypred.shape()[0];
        grad /= nsamples;
    }
    
    return grad;
}
