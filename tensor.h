#ifndef TENSOR_H
#define TENSOR_H
#include <stdexcept>
#include <cstdlib>
#include <iostream>
#include "uint.h"


template <class ElType>
class tensor
{
	public:


		tensor(uint size, ElType* dataPtr)
		:
			startPtr_(dataPtr),
			size_(size)
		{
			endPtr_ = startPtr_ + size_;
			ElType** trs = (ElType**)malloc(size_ * sizeof(ElType*));
			if 	(trs == NULL) throw "tensor malloc error";
			else 	mixedPtr_ = trs;
		}

		// Use this when have no tensor at hand
		tensor(uint row, uint col)
		:
			row_(row),
			col_(col),
			size_(row_ * col_)
		{
		
			ElType* els = (ElType*)malloc(size_ * sizeof(ElType));
			if (els == NULL) throw "tensor malloc error";
			else
			{
				startPtr_ = els;
			}	
			endPtr_ = startPtr_ + size_;


			ElType** trs = (ElType**)malloc(size_ * sizeof(ElType*));
			if (trs == NULL) throw "tensor malloc error";
			else
			{
				mixedPtr_ = trs;
				
				for(uint mix_iter = 0; mix_iter < size_; mix_iter++)
				{
					mixedPtr_[mix_iter] = startPtr_ + mix_iter;
				}

			}	
		}

		tensor(uint row, uint col, uint val)
		:
			row_(row),
			col_(col),
			size_(row_ * col_)
		{
		
			ElType* els = (ElType*)malloc(size_ * sizeof(ElType));
			if (els == NULL) throw "tensor malloc error";
			else
			{
				startPtr_ = els;
				for(uint iter = 0; iter < size_; iter++)
				{
					startPtr_[iter] = val;
				}
				endPtr_ = startPtr_ + size_;
			}	


			ElType** trs = (ElType**)malloc(size_ * sizeof(ElType*));
			if (trs == NULL) throw "tensor malloc error";
			else
			{
				mixedPtr_ = trs;
				
				for(uint mix_iter = 0; mix_iter < size_; mix_iter++)
				{
					mixedPtr_[mix_iter] = startPtr_ + mix_iter;
				}
			}	
		}

		tensor(tensor<ElType>&& other)
		{
			startPtr_ 	= other.startPtr_;
			mixedPtr_ 	= other.mixedPtr_;
			endPtr_		= other.endPtr_;
			row_		= other.row_;
			col_		= other.col_;
			size_		= other.size_;

			other.startPtr_ = nullptr;
                        other.mixedPtr_ = nullptr;
                        other.endPtr_   = nullptr;
			
		}

		tensor(const tensor<ElType>& other)
			:
				row_(other.row_),
				col_(other.col_),
				size_(col_ * row_)
			{
			
				
			
				ElType* els = (ElType*)malloc(size_ * sizeof(ElType));
				if (els == NULL) throw "tensor malloc error";
				else
				{
					startPtr_ = els;
					for(uint iter = 0; iter < size_; iter++)
					{
						startPtr_[iter] = *other.mixedPtr_[iter];
					}
					endPtr_ = startPtr_ + size_;
				}	


				ElType** trs = (ElType**)malloc(size_ * sizeof(ElType*));
				if (trs == NULL) throw "tensor malloc error";
				else
				{
					mixedPtr_ = trs;
					
					for(uint mix_iter = 0; mix_iter < size_; mix_iter++)
					{
						mixedPtr_[mix_iter] = startPtr_ + mix_iter;
					}
				}
			}
		~tensor()
		{
			free(mixedPtr_);
			if (isTranspose_ == 0) 
			free(startPtr_);

		}

		tensor<ElType>& operator=(const tensor<ElType>& other)
		{
			if(col_ != other.col_ && row_ != other.row_)
			{
				std::cerr << "Number of Columns and Number of Rows should match" 
				<< std::endl;
				exit(EXIT_FAILURE);
			}
			else
			{
				for(uint iter = 0; iter < size_; iter++)
				{
					startPtr_[iter] = *other.mixedPtr_[iter];
				}
			}

			return *this;
		}
		tensor<ElType>& operator=(tensor<ElType>&& other)
		{
			startPtr_ 	= other.startPtr_;
			mixedPtr_ 	= other.mixedPtr_;
			endPtr_		= other.endPtr_;
			row_		= other.row_;
			col_		= other.col_;
			size_		= other.size_;

			other.startPtr_ = nullptr;
                        other.mixedPtr_ = nullptr;
                        other.endPtr_   = nullptr;
			other.isTranspose_ = false;
			
			return *this;
		}

//------------------
		ElType* getPtr() const
		{
			return startPtr_;
		}
		

		
		void printLinear() const
		{
			std::cout << "startPtr_ : ";
			for(uint iter = 0; iter < size_; iter++)
			{
			
				std::cout << " " << startPtr_ + iter << " ";
			}
			std::cout << "\n";

			std::cout << "mixedPtr_: ";
			for(uint iter = 0; iter < size_; iter++)
			{
			
				std::cout << " " << mixedPtr_[iter] << " ";

			}
			std::cout << "\n";

		}

		void print() const
		{
			uint ctr = 0;
			ElType** iterPtr = mixedPtr_;
			std::cout << "| ";
			while(iterPtr != mixedPtr_ + size_)
			{
				std::cout << **iterPtr << "\t\t";
				iterPtr++;
				ctr++;
				if (ctr % col_ == 0)
				{
					if(ctr == size_) std::cout << "\b\b\b\b\b\b\b\b\b\b|\n";
					else 		 std::cout << "\b\b\b\b\b\b\b\b\b\b|\n| ";
				}	 

			}

		std::cout << "----" << std::endl;
		}

		void set(uint value, uint index)
		{
		
			startPtr_[index] = value;
		}

		void setInOrder()
		{
			uint index = 0;
			ElType* customPtr = startPtr_ + index;
			while(customPtr != endPtr_)
			{
			
				set(index, index);
				index++;
				customPtr++;
			}
		}
//OPERATOR OVERLOADS------------------------------------------
		tensor operator[](uint desiredRow) const
		{
			ElType** rowStart = mixedPtr_ + (col_* (desiredRow));
			tensor<ElType> res = tensor(col_, startPtr_);
			res.col_ = this -> col_;
			res.row_ = 1;
			for(uint iter = 0; iter < col_; iter++)
			{
				res.mixedPtr_[iter] = *(rowStart + iter);
			}	

			return res;
		}
	
		// Transpose
		tensor operator~()
		{
			//This is no good. res is local. It's freed after scope.
			//But it points to same, i.e startPtr = this -> startPtr.
			//Then in main *this is freed when hits return 0.
			//This results in segFault. It tries to free a pointer
			//that's already freed. (res deleted in the first place).
			tensor<ElType> res = tensor<ElType>(size_, startPtr_);
			res.row_ = col_;
			res.col_ = row_;
			for(uint cter = 0; cter < row_ * col_; cter++)
			{
				ElType* tempPtr = startPtr_ + cter;
				uint transposedIndex = mapPtrTranspose(startPtr_, tempPtr);
				res.mixedPtr_[transposedIndex] = tempPtr;
			}
			res.isTranspose_ = true;
			res.print();
			isTranspose_ = true;

			tensor<float>* Adress_res  = &res;
			return res;
		}

		void operator=(std::initializer_list<ElType> lst)
		{
			if (lst.size() != row_ * col_)
			{
				std::cerr << "check dimensions of init_list.";
				exit(EXIT_FAILURE);
			}
			uint i = 0;
			for(float val : lst)
			{
				if(i == size_) break;
				startPtr_[i] = val; 
				i++;
			}

		}

		//If you dont pass by reference, it tries to copy the argument. That results in
		//shallow copy which inevitably results in segmentation fault because it just copies
		//the data members which is supposed to be dynamically allocated. Then it tries to delete
		//the pointer that's not dynamically allocated.
		// TODO: Deep copy constructor or just use reference operator or ptr. 
		tensor operator+(const tensor& Tensor1)
		{
			tensor<ElType> res(row_, col_);
			
			for (uint iter = 0; iter < size_; iter++)
			{
				ElType* srcFirst 	= mixedPtr_[iter];
				ElType* srcSecond 	= Tensor1.mixedPtr_[iter];
				res.startPtr_[iter] = *srcFirst + *srcSecond;
			}
			res.print();
			return res;
			
		}

		tensor operator-(const tensor& Tensor1)
		{
			tensor<ElType> res(row_, col_);
			
			for (uint iter = 0; iter < size_; iter++)
			{
				ElType* srcFirst 	= mixedPtr_[iter];
				ElType* srcSecond 	= Tensor1.mixedPtr_[iter];
				res.startPtr_[iter] = *srcFirst - *srcSecond;
			}
			res.print();
			return res;
			
		}
                                              
		tensor operator*(const tensor& Tensor1)
		{
 			tensor<ElType> res(row_, Tensor1.col_);
			if(col_ != Tensor1.row_)
			{
				std::cerr << "check dimensions of matrices."
				<<  "This: " << &Tensor1;
				exit(EXIT_FAILURE);
			}
			else{
			
			for(uint iter = 0; iter< res.size_; iter++)
			{

				ElType target = 0;
				uint row_index = iter / res.col_;
				uint col_index = iter % res.col_;
				
				


				//ElType may not be scalar such that it is not necessarily 0. 
				//This conflicts with templification?
				//TODO: initialize such that it is kinda NULL.(zero in some sense but it not
				//need to be scalar)
				for(uint inner = 0; inner< col_; inner++)
				{
					ElType first 	= *mixedPtr_[row_index * col_ + inner];
					ElType second 	= *Tensor1.mixedPtr_[col_index + Tensor1.col_ * inner]; 
					
					target	+= first * second;
					
				}
				res.startPtr_[iter] = target;
			}
				
			}
			res.print();
			tensor<float>* Adress_res  = &res;
			return res;
		}                             
                                              
		tensor operator/(const ElType scalar)
		{
 			tensor<ElType> res(row_, col_);
			for(uint iter = 0; iter < size_; iter++)
			{
				
				ElType old = *mixedPtr_[iter];
				ElType newVal = old / scalar;
				res.startPtr_[iter] = newVal;
			}
			res.print();
			return res;
			
		}
		// This is strictly used for skew matrices.
		tensor operator<<(const tensor& Tensor1)
		{
 			tensor<ElType> skew(3, 3);
			ElType p = *mixedPtr_[0];
			ElType q = *mixedPtr_[1];
			ElType r = *mixedPtr_[2];

			skew ={	0,	-r, 	q,
			      	r,	0,	-p,
				-q,	p,	0};
			
 			tensor<ElType> res(3, 1);
			res = skew * Tensor1;
			return res;
			
		}


		

	private:
		uint		row_;
		uint		col_;
		ElType* 	startPtr_;
		ElType* 	endPtr_;
		// This is for transpose
		ElType**	mixedPtr_;
		uint		size_;	
		bool isTranspose_ = 0;

		uint mapPtrTranspose(ElType* start, ElType* normal) const
		{
			uint index = normal - start;

			uint row_index = index / col_;
			uint col_index = index % col_;
			uint newIndex = row_index + col_index * row_;
			return newIndex;
		}
		void setMixedPtr_()
		{
		
			
		}
};
#endif
