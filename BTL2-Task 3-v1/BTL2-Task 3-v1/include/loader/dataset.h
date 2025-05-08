
#ifndef DATASET_H
#define DATASET_H
#include "tensor/xtensor_lib.h"
using namespace std;

template<typename DType, typename LType>
class DataLabel{
private:
    xt::xarray<DType> data;
    xt::xarray<LType> label;
public:
    DataLabel(xt::xarray<DType> data,  xt::xarray<LType> label):
    data(data), label(label){
    }
    xt::xarray<DType> getData() const{ return data; }
    xt::xarray<LType> getLabel() const{ return label; }
};

template<typename DType, typename LType>
class Batch{
private:
    xt::xarray<DType> data;
    xt::xarray<LType> label;
public:
    Batch(xt::xarray<DType> data,  xt::xarray<LType> label):
    data(data), label(label){
    }
    virtual ~Batch(){}
    xt::xarray<DType>& getData(){return data; }
    xt::xarray<LType>& getLabel(){return label; }
};


template<typename DType, typename LType>
class Dataset{
private:
public:
    Dataset(){};
    virtual ~Dataset(){};
    
    virtual int len()=0;
    virtual DataLabel<DType, LType> getitem(int index)=0;
    virtual xt::svector<unsigned long> get_data_shape()=0;
    virtual xt::svector<unsigned long> get_label_shape()=0;
    
};

//////////////////////////////////////////////////////////////////////
template <typename DType, typename LType>
class TensorDataset : public Dataset<DType, LType> {
    private:
        xt::xarray<DType> data;
        xt::xarray<LType> label;
        xt::svector<unsigned long> data_shape, label_shape;

    public:
        TensorDataset(xt::xarray<DType> data, xt::xarray<LType> label) {
            this->data = data;
            this->label = label;
            
            data_shape = xt::svector<unsigned long>(data.shape().begin(), data.shape().end());
            label_shape = xt::svector<unsigned long>(label.shape().begin(), label.shape().end());
        }


        int len() {
            return data.shape()[0];
        }

        DataLabel<DType, LType> getitem(int index) {
        if (index < 0 || index >= this->len()) {
            throw std::out_of_range("Index is out of range!");
        }
        xt::xarray<DType> dataItem = xt::view(data, index);
        xt::xarray<LType> labelItem = label;
        if (label.dimension() > 0) {
            labelItem = xt::view(label, index);
        } 
        
        return DataLabel<DType, LType>(dataItem, labelItem);
        }


        xt::svector<unsigned long> get_data_shape() { return data_shape; }

        xt::svector<unsigned long> get_label_shape() { return label_shape; }
};



#endif /* DATASET_H */

