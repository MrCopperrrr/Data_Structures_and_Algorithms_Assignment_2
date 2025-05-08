/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt
 * to change this license Click
 * nbfs://nbhost/SystemFileSystem/Templates/cppFiles/class.cc to edit this
 * template
 */

/*
 * File:   Softmax.cpp
 * Author: ltsach
 *
 * Created on August 25, 2024, 2:46 PM
 */

#include "layer/Softmax.h"

#include <filesystem>  //require C++17

#include "ann/functions.h"
#include "sformat/fmt_lib.h"
namespace fs = std::filesystem;

Softmax::Softmax(int axis, string name) : m_nAxis(axis) {
  if (trim(name).size() != 0)
    m_sName = name;
  else
    m_sName = "Softmax_" + to_string(++m_unLayer_idx);
}

Softmax::Softmax(const Softmax& orig) {}

Softmax::~Softmax() {}

xt::xarray<double> Softmax::forward(xt::xarray<double> Z) {
    m_aCached_Y = softmax(Z, m_nAxis);
    return m_aCached_Y;
}

xt::xarray<double> Softmax::backward(xt::xarray<double> deltaY) {
  double_tensor Y = m_aCached_Y;
  double_tensor diagstackofY = diag_stack(Y);
  double_tensor outerstackofY = outer_stack(Y, Y);
  double_tensor Jacobian_matrix = diagstackofY - outerstackofY;
  double_tensor deltaZ = matmul_on_stack(Jacobian_matrix, deltaY);
  
  return deltaZ;
}

string Softmax::get_desc() {
  string desc = fmt::format("{:<10s}, {:<15s}: {:4d}", "Softmax",
                            this->getname(), m_nAxis);
  return desc;
}
