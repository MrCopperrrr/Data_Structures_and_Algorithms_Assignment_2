/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/file.h to edit this template
 */

/* 
 * File:   dataloader.h
 * Author: ltsach
 *
 * Created on September 2, 2024, 4:01 PM
 */

#ifndef DATALOADER_H
#define DATALOADER_H
#include "tensor/xtensor_lib.h"
#include "loader/dataset.h"

using namespace std;

template <typename DType, typename LType>
class DataLoader {
public:
    class Iterator;//forward declaration
private:
    Dataset<DType, LType>* ptr_dataset;
    int batch_size;
    bool shuffle;
    bool drop_last;
    int m_seed;
    int nbatch;

    // những biến khai báo thêm
    xt::xarray<unsigned long>index_list;
    int index_list_size; //index_list.size()
    xt::svector<unsigned long> BdataS, BlabelS;//BdataS = ptr_dataset->get_data_shape(); BlabelS = ptr_dataset->get_label_shape();
    
public:
  //Constructor
    DataLoader(Dataset<DType, LType>* ptr_dataset, 
                                    int batch_size, 
                                    bool shuffle = true, 
                                    bool drop_last = false, 
                                    int seed = -1) {//seed =0 để test///////////////////////////////////////////////////////////////////////////////////////////////////
    //khai báo 1 số biến
      this->ptr_dataset = ptr_dataset;
      this->batch_size = batch_size;
      this->shuffle = shuffle;
      this->m_seed = seed;
      this->drop_last = drop_last;

      index_list = xt::arange(ptr_dataset->len()); //tạo index_list từ 0 đến len của dataset
      index_list_size = index_list.size(); //lấy size của index_list
      nbatch = ptr_dataset->len()/batch_size;
      BdataS = ptr_dataset->get_data_shape();
      BlabelS = ptr_dataset->get_label_shape();
    //hết khai báo biến  
      
    //nếu drop_last = true và dư != 0 thì index_list_size -= dư
      int remain = index_list_size % batch_size;
      if(drop_last && remain != 0){
          index_list_size -= remain;//trừ đi phần dư 
      }
    //khai báo 2 biến BdataS và BlabelS để lưu kích thước của data và label trong 1 batch
      BdataS[0] = batch_size;
      BlabelS[0] = batch_size;
    //shuffle 
      if (shuffle){
          if(m_seed >= 0)
          xt::random::seed(m_seed);
          xt::random::shuffle(index_list);
      }
      if(index_list_size < batch_size)
          index_list_size = 0;    
    }
  //Destructor  
    virtual ~DataLoader() {}


    int get_batch_size(){ return batch_size; }
    int get_sample_count(){ return ptr_dataset->len(); }
    int get_total_batch(){return int(ptr_dataset->len()/batch_size); }


  //Iterator
  //Bắt đầu và kết thúc của mỗi batch
    Iterator begin() {
        return Iterator(this, 0);
    }

    Iterator end() {
        return Iterator(this,index_list_size );
    }

    class Iterator {//Iterator nằm trong class DataLoader
    private:
    //loader dùng để load data
        DataLoader<DType, LType>* loader;
        int index;

    public:
      //Constructor
        Iterator(DataLoader<DType, LType>* loader, int index) :loader(loader), index(index) {}

      //Destructor

      //Operator= dùng để gán giá trị của 1 Iterator khác cho Iterator hiện tại
        Iterator& operator=(const Iterator& iterator) {
            if (this != iterator)
            {
                loader = iterator.loader;
                index = iterator.index;
            }
            return *this;
        }
      //Operator& dùng để trả về giá trị của Iterator    
        // Toán tử tăng (prefix increment operator) trả về giá trị của Iterator
        Iterator& operator++() {
            // Kiểm tra nếu việc tăng index lên 1.5 lần batch_size vượt quá kích thước của index_list
            if (index + static_cast<int>(loader->batch_size * 2) > loader->index_list_size) {
                // Nếu đúng, tăng index lên phần còn lại của index_list
                index += loader->index_list_size - index;
            } else {
                // Nếu sai, tăng index lên bằng batch_size
                index += loader->batch_size;
            }     
            // Trả về chính đối tượng Iterator hiện tại
            return *this;
        }
        // Toán tử tăng hậu tố (postfix increment operator) trả về giá trị của Iterator trước khi tăng
        Iterator operator++(int) {
            // Tạo một Iterator tạm thời và gán giá trị của Iterator hiện tại cho nó
            Iterator temp = *this;
            
            // Kiểm tra nếu việc tăng index lên 1.5 lần batch_size vượt quá kích thước của index_list
            if (index + static_cast<int>(loader->batch_size * 2) > loader->index_list_size) {
                // Nếu đúng, tăng index lên phần còn lại của index_list
                index += loader->index_list_size - index;
            } else {
                // Nếu sai, tăng index lên bằng batch_size
                index += loader->batch_size;
            }
            
            // Trả về Iterator tạm thời (giá trị của Iterator trước khi tăng)
            return temp;
      }
      //Operator!= dùng để so sánh 2 Iterator
        bool operator!=(const Iterator& other) const {
            return this->index != other.index;
        }
      //Operator* dùng để trả về 1 batch
        Batch<DType, LType> operator*() const {
        //khai báo 1 số biến
          xt::xarray<DType> dataB;
          xt::xarray<LType> labelB;
          //nếu có label thì is_Labeled = true
          bool is_Labeled = !loader->BlabelS.empty();//bool is_Labeled = !loader->BlabelS.size() == 0;
          int last_index;//index cuoi cung cua 1 batch
          int loader_batch_size = loader->batch_size;
          int loader_index_list_size = loader->index_list_size;
        //hết khai báo

        //nếu index cuối cùng của 1 batch lớn hơn hoặc bằng index cuối cùng của index_list thì last_index = index + loader_batch_size
          if((loader_index_list_size - loader_batch_size - index) >= loader_batch_size){
            last_index = index + loader_batch_size;
                   
          }
          else{//ngược lại last_index = index_list_size
            last_index = loader->index_list_size;
            loader->BdataS[0] = loader->BlabelS[0] = loader->index_list_size - index;
            //loader->BlabelS[0] = loader->index_list_size - index;             
          }
        //kiểm tra label  
          if(is_Labeled)
              labelB = xt::xarray<LType>::from_shape(loader->BlabelS);
          dataB = xt::xarray<DType>::from_shape(loader->BdataS); 
          
        //lặp qua các phần tử của index_list từ index đến last_index
        //lấy data và label của mỗi phần tử và gán vào dataB và labelB
          for (int i = 0; i < (last_index - index); i++){      
              DataLabel<DType, LType> data_label = loader->ptr_dataset->getitem(loader->index_list[i+index]); 
              xt::view(dataB,i,xt::all()) = data_label.getData();
              if(is_Labeled){
                xt::view(labelB,i,xt::all()) = data_label.getLabel();
              }
          }
                
          return Batch<DType, LType>(dataB, labelB);
        }
    };
};

#endif /* DATALOADER_H */

