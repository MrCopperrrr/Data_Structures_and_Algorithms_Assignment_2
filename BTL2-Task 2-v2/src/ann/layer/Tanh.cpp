/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt
 * to change this license Click
 * nbfs://nbhost/SystemFileSystem/Templates/cppFiles/class.cc to edit this
 * template
 */

/*
 * File:   Tanh.cpp
 * Author: ltsach
 *
 * Created on September 1, 2024, 7:03 PM
 */

#include "layer/Tanh.h"

#include "ann/functions.h"
#include "sformat/fmt_lib.h"

Tanh::Tanh(string name) {
  if (trim(name).size() != 0)
    m_sName = name;
  else
    m_sName = "Tanh_" + to_string(++m_unLayer_idx);
}

Tanh::Tanh(const Tanh& orig) { m_sName = "Tanh_" + to_string(++m_unLayer_idx); }

Tanh::~Tanh() {}

xt::xarray<double> Tanh::forward(xt::xarray<double> X) {
  m_aCached_Y=xt::tanh(X);
  return m_aCached_Y;
}
xt::xarray<double> Tanh::backward(xt::xarray<double> DY) {
  xt::xarray<double> dX = DY * (1 - xt::pow(m_aCached_Y, 2));
  return dX;
}

string Tanh::get_desc() {
  string desc = fmt::format("{:<10s}, {:<15s}:", "Tanh", this->getname());
  return desc;
}
