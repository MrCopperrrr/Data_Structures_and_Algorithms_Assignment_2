/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt
 * to change this license Click
 * nbfs://nbhost/SystemFileSystem/Templates/cppFiles/class.cc to edit this
 * template
 */

/*
 * File:   ReLU.cpp
 * Author: ltsach
 *
 * Created on August 25, 2024, 2:44 PM
 */

#include "layer/ReLU.h"

#include "ann/functions.h"
#include "sformat/fmt_lib.h"

/*
ReLU (Rectified Linear Unit) là một hàm kích hoạt được sử dụng trong các mạng nơ-ron, chủ yếu cho các lớp ẩn trong mạng nơ-ron sâu.
giúp mạng nơ-ron có thể học được những hàm phi tuyến tính 
và có thể giảm bớt hiện tượng mất dần độ dốc (vanishing gradient), 
một vấn đề phổ biến khi dùng các hàm kích hoạt khác như sigmoid hoặc tanh
*/

ReLU::ReLU(string name) {
  if (trim(name).size() != 0)
    m_sName = name;
  else
    m_sName = "ReLU_" + to_string(++m_unLayer_idx);
}

ReLU::ReLU(const ReLU& orig) { m_sName = "ReLU_" + to_string(++m_unLayer_idx); }

ReLU::~ReLU() {}

xt::xarray<double> ReLU::forward(xt::xarray<double> X) {
  m_aMask = xt::where(X >= 0, true, false);
  return xt::where(m_aMask, X, 0);
}

xt::xarray<double> ReLU::backward(xt::xarray<double> DY) {
  // return DY * m_aMask;
  return xt::where(m_aMask, DY, 0);
}

string ReLU::get_desc() {
  string desc = fmt::format("{:<10s}, {:<15s}:", "ReLU", this->getname());
  return desc;
}