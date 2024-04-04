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
		}

		tensor(tensor<ElType>&& other)
		{
			startPtr_ 	= other.startPtr_;
			endPtr_		= other.endPtr_;
			row_		= other.row_;
			col_		= other.col_;
			size_		= other.size_;

			other.startPtr_ = nullptr;
                        other.endPtr_   = nullptr;
			
		}
		// Copy Constructor
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
						startPtr_[iter] = other.startPtr_[iter];
					}
					endPtr_ = startPtr_ + size_;
				}	
			}
		//Destructor
		~tensor()
		{
			free(startPtr_);

		}
		//Copy Assignment
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
					startPtr_[iter] = other.startPtr_[iter];
				}
			}

			return *this;
		}
		//Move Assignment
		tensor<ElType>& operator=(tensor<ElType>&& other)
		{
			startPtr_ 	= other.startPtr_;
			endPtr_		= other.endPtr_;
			row_		= other.row_;
			col_		= other.col_;
			size_		= other.size_;

			other.startPtr_ = nullptr;
                        other.endPtr_   = nullptr;
			
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
			std::cout << std::endl;

			std::cout << std::endl;

		}

		void print() const
		{
			uint ctr = 0;
			ElType* iterPtr = startPtr_;
			std::cout << "| ";
			while(iterPtr != startPtr_ + size_)
			{
				std::cout << *iterPtr << "\t\t";
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

		ElType get() const
		{
			return *startPtr_;
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
		void set(uint i, uint j, ElType val)
		{
			startPtr_[i * col_ + j] = val;
		}
//OPERATOR OVERLOADS------------------------------------------
		tensor operator[](uint i) const
		{
			try
			{
				tensor<ElType> res = tensor(1, col_);
				if (i <= row_ && i > 0)
				{
					ElType* firstPtr = startPtr_ + ((i - 1) * col_);
					for(uint iter = 0; iter < col_; iter++)
					{
						*(res.startPtr_ + iter) = firstPtr[iter];
					}	
					
					return res;
				}
				else throw (400);
			}
			catch(int errorId)
			{
			
				std::cerr << "Index is out of bound." << std::endl;
				std::cerr << "Err:" << errorId << std::endl;
				exit(EXIT_FAILURE);
			}
		}
		
		ElType operator()(uint i, uint j) const
		{
			try
			{
				if(i <= row_ && j <= col_)
				{
				
					return startPtr_[(i - 1) * col_ + (j - 1)];
					
				}
				else throw 401;
				
			}
			catch(int errorId)
			{
				std::cerr << "Index is out of bound." << std::endl;
				std::cerr << "Err:" << errorId << std::endl;
				exit(EXIT_FAILURE);
			}
		}
	
		// Transpose
		tensor operator~() const
		{
			//This is no good. res is local. It's freed after scope.
			//But it points to same, i.e startPtr = this -> startPtr.
			//Then in main *this is freed when hits return 0.
			//This results in segFault. It tries to free a pointer
			//that's already freed. (res deleted in the first place).
			tensor<ElType> res = tensor<ElType>(col_, row_);
			for(uint cter = 0; cter < row_ * col_; cter++)
			{
				ElType* tempPtr = startPtr_ + cter;
				uint transposedIndex = mapPtrTranspose(startPtr_, tempPtr);
				res.startPtr_[transposedIndex] = *tempPtr;
			}
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

		tensor operator+(const tensor& other)
		{
			try
			{
				if(other.col_ == col_ && other.row_ == row_)
				{
					tensor<ElType> res(row_, col_);
					
					for (uint iter = 0; iter < size_; iter++)
					{
						ElType srcFirst		= startPtr_[iter];
						ElType srcSecond	= other.startPtr_[iter];
						res.startPtr_[iter] = srcFirst + srcSecond;
					}
					return res;
				}
				else throw 403;
			}
			catch(int errorId)
			{
				std::cerr << "Dimensions don't match" << std::endl;
				std::cerr << "Err:" << errorId << std::endl;
				exit(EXIT_FAILURE);
			}

		}
		tensor operator-(const tensor& other)
		{
			try
			{
				if(other.col_ == col_ && other.row_ == row_)
				{
					tensor<ElType> res(row_, col_);
					
					for (uint iter = 0; iter < size_; iter++)
					{
						ElType srcFirst		= startPtr_[iter];
						ElType srcSecond	= other.startPtr_[iter];
						res.startPtr_[iter] = srcFirst - srcSecond;
					}
					return res;
				}
				else throw 404;
			}
			catch(int errorId)
			{
				std::cerr << "Dimensions don't match" << std::endl;
				std::cerr << "Err:" << errorId << std::endl;
				exit(EXIT_FAILURE);
			}

		}
                                              
		tensor operator*(const tensor& other) const
		{
			try
			{
				tensor<ElType> res(row_, other.col_);
				if(col_ == other.row_)
				{
				
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
							ElType first 	= startPtr_[row_index * col_ + inner];
							ElType second 	= other.startPtr_[col_index + other.col_ * inner]; 
							
							target	+= first * second;
							
						}
						res.startPtr_[iter] = target;
					}
					return res;
				}
				else throw 405;
				
			}
			catch(int errorId)
			{
				std::cerr << "Dimensions don't match" << std::endl;
				std::cerr << "Err:" << errorId << std::endl;
				exit(EXIT_FAILURE);
			}
		}                             
                                              
		tensor operator/(const ElType scalar) const
		{
			try
			{
				if(scalar != 0)
				{
					tensor<ElType> res(row_, col_);
					for(uint iter = 0; iter < size_; iter++)
					{
						ElType old = startPtr_[iter];
						ElType newVal = old / scalar;
						res.startPtr_[iter] = newVal;
					}
					return res;
				}
				else throw 406;
			}
			catch(int errorId)
			{
				std::cerr << "Division by Zero" << std::endl;
				std::cerr << "Err:" << errorId << std::endl;
				exit(EXIT_FAILURE);
			}
		}
		// Cross Product of two vectors.
		tensor operator%(const tensor& other)
		{
			try
			{
				if(row_ == 3 && col_ == 1 && other.row_ == 3 && other.col_ == 1)
				{
					tensor<ElType> skew(3, 3);
					ElType p = startPtr_[0];
					ElType q = startPtr_[1];
					ElType r = startPtr_[2];

					skew ={	0,	-r, 	q, 
						r,	0,	-p,
						-q,	p,	0};
					tensor<ElType> res(3, 1);
					res = skew * other;
					return res;
					
				}
				else throw 407;
			}
			catch(int errorId)
			{
				std::cerr << "Division by Zero" << std::endl;
				std::cerr << "Err:" << errorId << std::endl;
				exit(EXIT_FAILURE);
			}
		}


	private:
		uint		row_;
		uint		col_;
		ElType* 	startPtr_;
		ElType* 	endPtr_;
		// This is for transpose
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
