#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>
using namespace std;

#include <filesystem> //require C++17
namespace fs = std::filesystem;

#include "list/listheader.h"
#include "sformat/fmt_lib.h"
#include "tensor/xtensor_lib.h"
#include "ann/annheader.h"
#include "loader/dataset.h"
#include "loader/dataloader.h"
#include "config/Config.h"
#include "dataset/DSFactory.h"
#include "optim/Adagrad.h"
#include "optim/Adam.h"
#include "modelzoo/twoclasses.h"
#include "modelzoo/threeclasses.h"


//test hàm backward của FCLayer ĐÃ PASS
void test_backward_batch() {
  // DATA
  FCLayer fc_layer(2, 3, true);
  xt::xarray<double> weights = {{0.2, 0.5}, {0.3, 0.7}, {0.4, 0.9}};
  xt::xarray<double> bias = {0.1, -0.1, 0.2};
  fc_layer.set_weights(weights);
  fc_layer.set_bias(bias);
  xt::xarray<double> X = {{1.0, 2.0}, {0.5, 1.5}, {1.5, 0.5}};
  fc_layer.set_working_mode(true);
  fc_layer.forward(X);
  xt::xarray<double> DY = {
      {1.0, 0.5, -0.5}, {0.5, -0.5, 0.0}, {0.0, 1.0, -1.0}};

  // expect use mean
  xt::xarray<double> expected_grad_W = {
      {0.416667, 0.916667}, {0.583333, 0.25}, {-0.666667, -0.5}};
  xt::xarray<double> expected_grad_b = {0.5, 0.333333, -0.5};
  xt::xarray<double> expected_dx = {{0.15, 0.4}, {-0.05, -0.1}, {-0.1, -0.2}};

  // Thực hiện backward
  xt::xarray<double> dX = fc_layer.backward(DY);

  // public m_aGrad_W and m_aGrad_b in FCLayer
  cout << fc_layer.m_aGrad_W << endl;
  cout << fc_layer.m_aGrad_b << endl;
  cout << dX << endl;
  assert(xt::allclose(fc_layer.m_aGrad_W, expected_grad_W));
  assert(xt::allclose(fc_layer.m_aGrad_b, expected_grad_b));
  assert(xt::allclose(dX, expected_dx));
  std::cout << "Backward batch test passed!" << std::endl;
}


//test softmax backward đã PASS
void test_softmax_backward() {
    // Khởi tạo dữ liệu
    Softmax softmax_layer;
    softmax_layer.set_working_mode(true);
    xt::xarray<double> X = {{1.0, 2.0, 3.0}, {1.0, -1.0, 0.0}};
    softmax_layer.forward(X);
    xt::xarray<double> DY = {{0.1, 0.2, -0.3}, {-0.1, 0.3, 0.0}};

    // Kết quả mong đợi
    xt::xarray<double> expected_DX = {{0.021754, 0.083605, -0.105359},
                                      {-0.040237, 0.030567, 0.00967}};

    // Thực hiện backward
    xt::xarray<double> DX = softmax_layer.backward(DY);

    // In kết quả
    std::cout << "DX: " << DX << std::endl;
    std::cout << "Expected DX: " << expected_DX << std::endl;

    // Kiểm tra xem DX và expected_DX có giống nhau không
    if (xt::allclose(DX, expected_DX)) {
        std::cout << "DX và expected_DX giống nhau." << std::endl;
    } else {
        std::cout << "DX và expected_DX không giống nhau." << std::endl;
    }

}



//test fclayer forward đã PASS
void test_forward_batch() {
  // DATA
  FCLayer fc_layer(2, 3, true);
  xt::xarray<double> weights = {{0.2, 0.5}, {0.3, 0.7}, {0.4, 0.9}};
  xt::xarray<double> bias = {0.1, -0.1, 0.2};
  fc_layer.set_weights(weights);
  fc_layer.set_bias(bias);
  xt::xarray<double> X = {{1.0, 2.0}, {0.5, 1.5}, {1.5, 0.5}};

  // expected
  xt::xarray<double> expected_output = {
      {1.3, 1.6, 2.4}, {0.95, 1.1, 1.75}, {0.65, 0.7, 1.25}};

  xt::xarray<double> output = fc_layer.forward(X);

  // result
  cout << output << endl;
  assert(xt::allclose(output, expected_output));
  std::cout << "Forward batch test passed!" << std::endl;
}


void mlpDemo1() {
    xt::random::seed(42);
    DSFactory factory("./config.txt");
    xmap<string, TensorDataset<double, double>*>* pMap = factory.get_datasets_2cc();
    TensorDataset<double, double>* train_ds = pMap->get("train_ds");
    TensorDataset<double, double>* valid_ds = pMap->get("valid_ds");
    TensorDataset<double, double>* test_ds = pMap->get("test_ds");
    DataLoader<double, double> train_loader(train_ds, 50, true, false);
    DataLoader<double, double> valid_loader(valid_ds, 50, false, false);
    DataLoader<double, double> test_loader(test_ds, 50, false, false);

    cout << "Train dataset: " << train_ds->len() << endl;
    cout << "Valid dataset: " << valid_ds->len() << endl;
    cout << "Test dataset: " << test_ds->len() << endl;

    int nClasses = 2;
    ILayer* layers[] = {
        new FCLayer(2, 50, true),
        new ReLU(),
        new FCLayer(50, nClasses, true),
        new Softmax()
    };

    MLPClassifier model("./config.txt", "2c-classification", layers, sizeof(layers)/sizeof(ILayer*));

    SGD optim(2e-3);
    CrossEntropy loss;
    ClassMetrics metrics(nClasses);

    model.compile(&optim, &loss, &metrics);
    model.fit(&train_loader, &valid_loader, 10);
    string base_path = "./models";
    // model.save(base_path + "/" + "2c-classification-1");
    double_tensor eval_rs = model.evaluate(&test_loader);
    cout << "Evaluation result on the testing dataset: " << endl;
    cout << eval_rs << endl;
}

void mlpDemo2() {
    xt::random::seed(42);
    DSFactory factory("./config.txt");
    xmap<string, TensorDataset<double, double>*>* pMap = factory.get_datasets_2cc();
    TensorDataset<double, double>* train_ds = pMap->get("train_ds");
    TensorDataset<double, double>* valid_ds = pMap->get("valid_ds");
    TensorDataset<double, double>* test_ds = pMap->get("test_ds");
    DataLoader<double, double> train_loader(train_ds, 50, true, false);
    DataLoader<double, double> valid_loader(valid_ds, 50, false, false);
    DataLoader<double, double> test_loader(test_ds, 50, false, false);

    int nClasses = 2;
    ILayer* layers[] = {
        new FCLayer(2, 50, true),
        new Sigmoid(),
        new FCLayer(50, nClasses, true),
        new Softmax()
    };

    MLPClassifier model("./config.txt", "2c-classification", layers, sizeof(layers)/sizeof(ILayer*));

    SGD optim(2e-3);
    CrossEntropy loss;
    ClassMetrics metrics(nClasses);

    model.compile(&optim, &loss, &metrics);
    model.fit(&train_loader, &valid_loader, 10);
    string base_path = "./models";
    // model.save(base_path + "/" + "2c-classification-1");
    double_tensor eval_rs = model.evaluate(&test_loader);
    cout << "Evaluation result on the testing dataset: " << endl;
    cout << eval_rs << endl;
}
void mlpDemo3() {
    xt::random::seed(42);
    DSFactory factory("./config.txt");
    xmap<string, TensorDataset<double, double>*>* pMap = factory.get_datasets_2cc();
    TensorDataset<double, double>* train_ds = pMap->get("train_ds");
    TensorDataset<double, double>* valid_ds = pMap->get("valid_ds");
    TensorDataset<double, double>* test_ds = pMap->get("test_ds");
    DataLoader<double, double> train_loader(train_ds, 50, true, false);
    DataLoader<double, double> valid_loader(valid_ds, 50, false, false);
    DataLoader<double, double> test_loader(test_ds, 50, false, false);

    int nClasses = 2;
    ILayer* layers[] = {
        new FCLayer(2, 50, true),
        new Tanh(),
        new FCLayer(50, nClasses, true),
        new Softmax()
    };

    MLPClassifier model("./config.txt", "2c-classification", layers, sizeof(layers)/sizeof(ILayer*));

    SGD optim(2e-3);
    CrossEntropy loss;
    ClassMetrics metrics(nClasses);

    model.compile(&optim, &loss, &metrics);
    model.fit(&train_loader, &valid_loader, 10);
    string base_path = "./models";
    // model.save(base_path + "/" + "2c-classification-1");
    double_tensor eval_rs = model.evaluate(&test_loader);
    cout << "Evaluation result on the testing dataset: " << endl;
    cout << eval_rs << endl;
}

int main(int argc, char** argv) {
    // cout << "Run FCLayer::forward" <<endl;
    // test_forward_batch();//FCLayer forward

    // cout << "Run FCLayer::backward" <<endl;
    // test_backward_batch();//FCLayer backward

    // cout << "Run Softmax::backward" <<endl;
    // test_softmax_backward();//Softmax backward

    //dataloader:
    //case_data_wo_label_1();
    //case_data_wi_label_1();
    //case_batch_larger_nsamples();
    
    //Classification:
    cout << "Run 2cc" << endl;
    twoclasses_classification();
    cout << "Finish 2cc" << endl;

    // cout << "Run 3cc" << endl;
    // threeclasses_classification();
    // cout << "Finish 3cc" << endl;

    cout << "Run MLP1" << endl;
    mlpDemo1();
    cout << "Finish MLP1" << endl;
    cout << "Run MLP2" << endl;
    mlpDemo2();
    cout << "Finish MLP2" << endl;
    cout << "Run MLP3" << endl;
    mlpDemo3();
    cout << "Finish MLP3" << endl;

  return 0;
}
