#ifndef TENSOR_H
#define TENSOR_H

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
		
		ElType* getPtr() const
		{
			return startPtr_;
		}

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
			tensor<ElType> res = tensor<ElType>(size_, startPtr_);
			res.row_ = col_;
			res.col_ = row_;
			for(uint cter = 0; cter < row_ * col_; cter++)
			{
				ElType* tempPtr = startPtr_ + cter;
				uint transposedIndex = mapPtrTranspose(startPtr_, tempPtr);
				res.mixedPtr_[transposedIndex] = tempPtr;
			}
			return res;
		}
		// TODO: make value to be of type ElType. For now I set it to be uint
		void set(uint value, uint index)
		{
			startPtr_[index] = value;
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
				std::cout << **iterPtr << " ";
				iterPtr++;
				ctr++;
				if (ctr % col_ == 0)
				{
					if(ctr == size_) std::cout << "|\n";
					else 		 std::cout << "|\n| ";
				}	 

			}

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

	private:
		uint		row_;
		uint		col_;
		ElType* 	startPtr_;
		ElType* 	endPtr_;
		// This is for transpose
		ElType**	mixedPtr_;
		uint		size_;	

		uint mapPtrTranspose(ElType* start, ElType* normal) const
		{
			uint index = normal - start;

			uint row_index = index / col_;
			uint col_index = index % col_;
			uint newIndex = row_index + col_index * row_;
			return newIndex;
		}

};
#endif
