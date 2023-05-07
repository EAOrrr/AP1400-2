#include "hw1.h"


using std::vector;  using std::cout;
using std::endl;

Matrix algebra::zeros(size_t n, size_t m){
    if(m <= 0 || n <= 0) throw std::logic_error("error");
    Matrix zero_matrix(n, vector<double>(m, 0));
    return zero_matrix;
}

Matrix algebra::ones(size_t n, size_t m){
    if(m <= 0 || n <= 0) throw std::logic_error("error");
    Matrix ones_matrix(n, vector<double>(m, 1));
    return ones_matrix;
}

Matrix algebra::random(size_t n, size_t m, double min, double max){
    if(m <= 0 || n <= 0) throw std::logic_error("error");
    if(min > max) throw std::logic_error("error");
    std:: mt19937 gen;
    std::uniform_real_distribution<double> distr(min, max);
    Matrix rand_matrix(n);
    for(vector<double>& row_vec: rand_matrix){
        row_vec.assign(m, distr(gen));
    }
    return rand_matrix;
}

void algebra::show(const Matrix& matrix){
    for(const vector<double>& row_vec: matrix){
        for(const double elem: row_vec){
            cout << std::left << std::setw(10) << std::setprecision(3) << elem << ' ';
        }
        cout << endl;
    }
}

Matrix algebra::multiply(const Matrix& matrix, double c){
    Matrix result = matrix;
    for(auto&row_vec: result){
        std::transform(row_vec.begin(), row_vec.end(), row_vec.begin(), [c](double n){return n * c;});
    }
    return result;
}

Matrix algebra::multiply(const Matrix& matrix1, const Matrix& matrix2){
    size_t m = matrix1.size(), p2 = matrix2.size();
    if(m == 0 || p2 == 0) return Matrix{};
    size_t p = matrix1.at(0).size(), n = matrix2.at(0).size();
    if(p != p2)
        throw std::logic_error("error");
    Matrix result;
    for(size_t i = 0; i < m; i ++){
        vector<double> row_vec;
        for(size_t j = 0; j < n; j++){
            double elem = 0;
            for (size_t k = 0; k < p; k++)
                elem += matrix1[i][k] * matrix2[k][j];
            row_vec.push_back(elem);
        }
        result.push_back(row_vec);
    }
    return result;
}

Matrix algebra::sum(const Matrix& matrix, double c){
    Matrix result = matrix;
    std::transform(result.begin(), result.end(), result.begin(), 
    [c](vector<double> row_vec){
        for(double& elem: row_vec) elem = elem + c;
        return row_vec;
    });
    return result;
}   

Matrix algebra::sum(const Matrix& matrix1, const Matrix& matrix2){
    // edge case: the size of 2 matrix 
    if(matrix1.empty() && matrix2.empty())
        return Matrix{};
    if(matrix1.size() != matrix2.size())
        throw std::logic_error("error");
    size_t n1 = matrix1.at(0).size(), n2 = matrix2.at(0).size();
    if(n1 != n2)
        throw std::logic_error("error");
    Matrix result;
    for(size_t i = 0; i < matrix1.size(); ++i){
        vector<double> row_vec;
        for(size_t j = 0; j < n1; ++j)
            row_vec.push_back(matrix1.at(i).at(j) + matrix2.at(i).at(j));
        result.push_back(row_vec);
    }
    return result;
}

Matrix algebra::transpose(const Matrix& matrix){
    if(matrix.size() == 0) return Matrix{};
    Matrix result;
    for(size_t j = 0; j < matrix.at(0).size(); ++j){
        vector<double> row_vec;
        for(size_t i = 0; i < matrix.size(); i++)
            row_vec.push_back(matrix.at(i).at(j));
        result.push_back(row_vec);
    }
    return result;
}

Matrix algebra::minor(const Matrix& matrix, size_t n, size_t m){
    // WARNING m, n cannot be out of the size matrix
    size_t row = matrix.size();
    if(row == 0)
        throw std::logic_error("error");
    size_t col = matrix.at(0).size();
    if(n >= row || m >= col)
        throw std::logic_error("error");
    Matrix result;
    for(int i = 0; i < row; i++){
        if(i == n) continue;
        vector<double> row_vec;
        std::copy(matrix[i].begin(), matrix[i].begin()+m, std::back_inserter(row_vec));
        std::copy(matrix[i].begin()+m+1, matrix[i].end(), std::back_inserter(row_vec));
        result.push_back(row_vec);

    }
    return result;
}

double algebra::determinant(const Matrix& matrix){
    if(matrix.empty()) return 1;
    if(matrix.size() != matrix.at(0).size())
        throw std::logic_error("error");
    return det_helper(matrix);
}

double det_helper(const Matrix& matrix){
    if(matrix.empty()) return 1;
    double det = 0;
    for(size_t i = 0; i < matrix.size(); ++i){
        det += matrix[0][i] * pow(-1, i) * det_helper(algebra::minor(matrix, 0, i));
    }
    return det;
}

Matrix algebra::inverse(const Matrix& matrix){
    double det = algebra::determinant(matrix);
    if(!det) throw std::logic_error("error");
    Matrix result;
    for(size_t i = 0; i < matrix.size(); i++){
        vector<double> row_vec;
        for(size_t j = 0; j < matrix.size(); ++j){
            row_vec.push_back(pow(-1, i+j)* algebra::determinant(algebra::minor(matrix, j, i))/det);
        }
        result.push_back(row_vec);
    }
    return result;
}

Matrix algebra::concatenate(const Matrix& matrix1, const Matrix& matrix2, int axis){
    if(axis == 0){
        if(matrix1.empty() && matrix2.empty())  return Matrix{};
        if((matrix1.empty() || matrix2.empty()) || (matrix1[0].size() != matrix2[0].size()))
            throw std::logic_error("error");
        Matrix result;
        std::copy(matrix1.begin(), matrix1.end(), std::back_inserter(result));
        std::copy(matrix2.begin(), matrix2.end(), std::back_inserter(result));
        return result;
    }
    if(axis == 1){
        if(matrix1.empty() && matrix2.empty())  return Matrix{};
        if(matrix1.size() != matrix2.size())
            throw std::logic_error("error");
        Matrix result;
        for(size_t i = 0; i < matrix1.size(); ++i){
            vector<double> row_vector;
            std::copy(matrix1[i].begin(), matrix1[i].end(), std::back_inserter(row_vector));
            std::copy(matrix2[i].begin(), matrix2[i].end(), std::back_inserter(row_vector));
            result.push_back(row_vector);
        }
        return result;
    }
    throw std::logic_error("error");
}

Matrix algebra::ero_swap(const Matrix& matrix, size_t r1, size_t r2){
    if(r1 >= matrix.size() || r2 >= matrix.size())
        throw std::logic_error("error");
    Matrix result(matrix.size());
    std::copy(matrix.begin(), matrix.end(), result.begin());
    result[r1].swap(result[r2]);
    return result;
}

Matrix algebra::ero_multiply(const Matrix& matrix, size_t r, double c){
    if(r >= matrix.size()) throw std::logic_error("error");
    Matrix result(matrix.size());
    std::copy(matrix.begin(), matrix.end(), result.begin());
    for(size_t i = 0; i < matrix[0].size(); ++i)
        result[r][i] *= c;
    return result;
}

Matrix algebra::ero_sum(const Matrix& matrix, size_t r1, double c, size_t r2){
    if(r1 >= matrix.size() || r2 >= matrix.size())
        throw std::logic_error("error");
    Matrix result;
    for(size_t r = 0; r < matrix.size(); ++r){
        vector<double> row_vec;
        if(r == r2){
            for(size_t i = 0; i < matrix[r].size(); ++i)
                row_vec.push_back(matrix[r][i] + c * matrix[r1][i]);
        }
        else{
            row_vec.resize(matrix[0].size());
            std::copy(matrix[r].begin(), matrix[r].end(), row_vec.begin());
        }
        result.push_back(row_vec);
    }
    return result;
}

Matrix algebra::upper_triangular(const Matrix& matrix){
    if (matrix.empty()) return Matrix{};
    if (matrix.size() != matrix[0].size()) throw std::logic_error("error");
    Matrix result = matrix;
    size_t pivor_row = 0;
    for(size_t c = 0; c < result[0].size(); ++c){
        size_t current_row = pivor_row + 1;
        for(;current_row < result.size(); current_row++){
            if(result[pivor_row][c] != 0) break;
            result = algebra::ero_swap(result, pivor_row, current_row);
        }
        if(result[pivor_row][c] == 0) continue;
        for(size_t r = pivor_row+1; r < result.size(); ++r){
                result = algebra::ero_sum(result, pivor_row, -result[r][c]/result[pivor_row][c], r);
        }
        pivor_row++;
    }
    return result;
}
