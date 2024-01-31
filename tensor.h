#ifndef TENSOR_H
#define TENSOR_H

#include <cstdlib>
#include <iostream>
#include "uint.h"

template <class ElType>
class tensor
{
	public:
		tensor(uint row, uint col, ElType* start)
		:
			row_(row),
			col_(col),
			startPtr_(start),
			endPtr_(start + col)
		{
			uint size = row_ * col_;
			ElType** trs = (ElType**)malloc(size * sizeof(ElType*));
			if (trs == NULL) throw "tensor malloc error";
			else
			{
				mixedPtr_ = trs;
				for(uint mix_iter = 0; mix_iter < size; mix_iter++)
				{
					mixedPtr_[mix_iter] = startPtr_ + mix_iter;
				}
			}	
		}
		// Use this when have no tensor at hand
		tensor(uint row, uint col)
		:
			row_(row),
			col_(col)
		{
			uint size = row_ * col_;
		
			ElType* els = (ElType*)malloc(size * sizeof(ElType));
			if (els == NULL) throw "tensor malloc error";
			else
			{
				startPtr_ = els;
			}	
			endPtr_ = startPtr_ + size;


			ElType** trs = (ElType**)malloc(size * sizeof(ElType*));
			if (trs == NULL) throw "tensor malloc error";
			else
			{
				mixedPtr_ = trs;
				for(uint mix_iter = 0; mix_iter < size; mix_iter++)
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
			ElType** customStart = mixedPtr_ + (col_* (desiredRow - 1));
			tensor<ElType> res = tensor(1, col_, *customStart);
			return res;
		}
	
		// Transpose
		tensor operator~()
		{
			tensor<ElType> res = tensor<ElType>(col_, row_, startPtr_);
			for(uint cter = 0; cter < row_ * col_; cter++)
			{
				 uint transposedIndex = mapPtrTranspose(startPtr_, startPtr_ + cter);
				res.mixedPtr_[transposedIndex] = startPtr_ + cter;
			}
			return res;
		}
		// TODO: make value to be of type ElType. For now I set it to be uint
		void set(uint value, uint index)
		{
			startPtr_[index] = value;
		}
		
		void printLinear()
		{
			std::cout << "startPtr_ : ";
			for(uint iter = 0; iter < row_ * col_; iter++)
			{
			
				std::cout << " " << startPtr_ + iter << " ";
			}
			std::cout << "\n";

			std::cout << "mixedPtr_: ";
			for(uint iter = 0; iter < row_ * col_; iter++)
			{
			
				std::cout << " " << mixedPtr_[iter] << " ";
			}
			std::cout << "\n";

		}



		void print() const
		{
			
			uint index = 0;
			for(uint rowIter = 0; rowIter < row_; rowIter++)
			{
			
				std::cout << "| "; 

				for(uint colIter = 0; colIter < col_; colIter++)
				{
				
					std::cout << " " << *mixedPtr_[index] << " ";
					index++;
						
				}
				std::cout << "|" << std::endl;
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
