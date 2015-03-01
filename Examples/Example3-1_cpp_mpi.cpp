/*
 * TextParser - Text Parsing Library
 *
 * Copyright (C) 2012-2014 Institute of Industrial Science, The University of Tokyo.
 * All rights reserved.
 *
 * Copyright (c) 2014 Advanced Institute for Computational Science, RIKEN.
 * All rights reserved.
 */

/** @file Example3_cpp.cpp
 * サンプルプログラム
 */
#ifdef ENABLE_MPI
#include "mpi.h"
#endif // ENABLE_MPI

#include <iostream>
#include <string>
#include <vector>
#include "TextParser.h"
#include "../config.h"


int scan_all_parameters(std::string filename)
{
    int ierror = 0;
    //    TextParser* tp=TextParser::get_instance();
    TextParser* tp=TextParser::get_instance_singleton();

    // ファイルの読み込み
    std::cout << "filename: " << filename << std::endl;
    ierror=tp->read_local(filename);
    if (ierror != 0) {
      std::cout <<  "ERROR in TextParser::read  file: " << filename 
	        << " ERROR CODE "<< ierror << std::endl;
        return ierror;
    }

    // 全てのパラメータのラベルを取得
    std::vector<std::string> labels;
    ierror=tp->getAllLabels(labels);
    if (ierror != 0){
        std::cout <<  "ERROR in TextParser::getAllLabels file: " << filename 
	        << " ERROR CODE "<< ierror << std::endl;
        return ierror;
    }

    for (int i = 0; i < labels.size(); i++) {
        std::cout << i << " " << labels[i] << std::endl;
	
        //std::string value = MGPPGetValue(labels[i], &ierror);
	std::string value;
	ierror=tp->getValue(labels[i],value);

        if (ierror!=0){
        std::cout <<  "ERROR in TextParser::getValue file: " << filename 
		    << " ERROR CODE "<< ierror << std::endl;
            return ierror;
        }
        std::cout << i << " " << value << std::endl;

        TextParserValueType type = tp->getType(labels[i], &ierror);
        if (ierror != 0){
            std::cout <<  "ERROR in TextParser::getType file: " << filename 
		        << " ERROR CODE "<< ierror << std::endl;
            return ierror;
        }
        std::cout << i << " value type: " << type << std::endl;

        if (type == TP_NUMERIC_VALUE ) {
            char cval = tp->convertChar(value, &ierror);
            if (ierror != 0) {
                std::cout <<  "ERROR in TextParser::convertChar file: " << filename 
		            << " ERROR CODE "<< ierror << std::endl;
                return ierror;
            }
            std::cout << i << " convert to char: "<< cval << std::endl;
            short sval = tp->convertShort(value, &ierror);
            if (ierror != 0) {
                std::cout <<  "ERROR in TextParser::convertShort file: " << filename 
		            << " ERROR CODE "<< ierror << std::endl;
                return ierror;
            }
            std::cout << i << " convert to short: "<< sval << std::endl;
            int ival = tp->convertInt(value, &ierror);
            if (ierror != 0) {
                std::cout <<  "ERROR in TextParser::convertInt file: " << filename 
		            << " ERROR CODE "<< ierror << std::endl;
                return ierror;
            }
            std::cout << i << " convert to int: "<< ival << std::endl;
            long lval = tp->convertLong(value, &ierror);
            if (ierror != 0) {
                std::cout <<  "ERROR in TextParser::convertLong file: " << filename 
		            << " ERROR CODE "<< ierror << std::endl;
                return ierror;
            }
            std::cout << i << " convert to long: "<< lval << std::endl;
            long long llval = tp->convertLongLong(value, &ierror);
            if (ierror != 0) {
                std::cout <<  "ERROR in TextParser::convertLongLong file: " << filename 
		            << " ERROR CODE "<< ierror << std::endl;
                return ierror;
            }
            std::cout << i << " convert to long long: "<< llval << std::endl;
            float fval = tp->convertFloat(value, &ierror);
            if (ierror != 0) {
                std::cout <<  "ERROR in TextParser::convertFloat file: " << filename 
		            << " ERROR CODE "<< ierror << std::endl;
                return ierror;
            }
            std::cout << i << " convert to float: "<< fval << std::endl;
            double dval = tp->convertDouble(value, &ierror);
            if (ierror != 0) {
                std::cout <<  "ERROR in TextParser::convertDouble file: " << filename 
		            << " ERROR CODE "<< ierror << std::endl;
                return ierror;
            }
	    //            std::cout << i << " convert to double: "<< dval << std::endl;

#ifdef ENABLE_MPI
		int myrank;
		MPI_Comm_rank(MPI_COMM_WORLD,&myrank);
		std::cout << i << " convert to double: "<< dval 
			  << " myrank "<< myrank<< std::endl;
#else
		std::cout << i << " convert to double: "<< dval <<std::endl;
#endif
	    
        } else if( type == TP_VECTOR_NUMERIC) {
	  std::vector<std::string> values;
	    ierror = tp->splitVector(value,values);
            if (ierror != 0) {
                std::cout <<  "ERROR in TextParser::SplitVector file: " << filename 
		            << " ERROR CODE "<< ierror << std::endl;
                return ierror;
            }
            for (int j = 0; j < values.size(); j++) {
                char cval = tp->convertChar(values[j], &ierror);
                if (ierror != 0){
                    std::cout <<  "ERROR in TextParser::convertChar file: " << filename 
		                << " ERROR CODE "<< ierror << std::endl;
                }
                short sval = tp->convertShort(values[j], &ierror);
                if (ierror != 0){
                    std::cout <<  "ERROR in TextParser::convertShort file: " << filename 
		                << " ERROR CODE "<< ierror << std::endl;
                }
                int ival = tp->convertInt(values[j], &ierror);
                if (ierror != 0){
                    std::cout <<  "ERROR in TextParser::convertInt file: " << filename 
		                << " ERROR CODE "<< ierror << std::endl;
                }
                long lval = tp->convertLong(values[j], &ierror);
                if (ierror != 0){
                    std::cout <<  "ERROR in TextParser::convertLong file: " << filename 
		                << " ERROR CODE "<< ierror << std::endl;
                }
                long long llval = tp->convertLongLong(values[j], &ierror);
                if (ierror != 0){
                    std::cout <<  "ERROR in TextParser::convertLongLong file: " << filename 
		                << " ERROR CODE "<< ierror << std::endl;
                }
                float fval = tp->convertFloat(values[j], &ierror);
                if (ierror != 0){
                    std::cout <<  "ERROR in TextParser::convertFloat file: " << filename 
		                << " ERROR CODE "<< ierror << std::endl;
                }
                double dval = tp->convertDouble(values[j], &ierror);
                if (ierror != 0){
                    std::cout <<  "ERROR in TextParser::convertDouble file: " << filename 
		                << " ERROR CODE "<< ierror << std::endl;
                }

#ifdef ENABLE_MPI
		int myrank;
		MPI_Comm_rank(MPI_COMM_WORLD,&myrank);
		std::cout <<"myrank " <<myrank << " ";
#else
		// do nothing
#endif		
		std::cout << j << " " << values[j]
			  << " char: " << cval
			  << " short: " << sval
			  << " int: " << ival
			  << " long: " << lval
			  << " long long: " << llval
			  << " float: " << fval
			  << " double: " << dval << std::endl;


            }

        } else if (type == TP_VECTOR_STRING) {
	  std::vector<std::string> values; 
	  ierror=tp->splitVector(value, values);
            if (ierror != 0){
                std::cout <<  "ERROR in TextParser::splitVector file: " << filename 
                    << " ERROR CODE "<< ierror << std::endl;
            }
            for (int j = 0; j < values.size(); j++) {
	            std::cout << j << " " << values[j] << std::endl;
            }
        }
    }
    labels.clear();

    // パラメータの削除
    ierror=tp->remove();
    if (ierror != 0) {
        std::cout <<  "ERROR in TextParser::Remove file: " << filename 
	        << " ERROR CODE "<< ierror << std::endl;
    }
    std::cout << std::endl;

    return ierror;
}

int main(int argc, char* argv[])
{
  int nprocs, myrank;
#ifdef ENABLE_MPI
  MPI_Init(&argc,&argv);
  MPI_Comm_size(MPI_COMM_WORLD,&nprocs);
  MPI_Comm_rank(MPI_COMM_WORLD,&myrank);
  std::cout << "MPI info nprocs="<<nprocs<<" myrank="<<myrank<<std::endl;
#endif //ENABLE_MPI

  //    std::string filename = "Input0-1.txt";
  std::string filename;
  if(myrank==0) {
    filename = "./tpp_examples/correct_label_1.txt";
  } else {
    filename = "./tpp_examples/correct_label_10.txt";
  }

    scan_all_parameters(filename);
    //    filename = "Input1-1.txt";
    //    scan_all_parameters(filename);
    //    filename = "Input4-1.txt";
    // scan_all_parameters(filename);
    // filename = "Input4-2.txt";
    // scan_all_parameters(filename);
#ifdef ENABLE_MPI
    MPI_Finalize();
#endif //ENABLE_MPI
    return 0;
}
