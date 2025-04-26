# General Matrix Multiplication (GEMM)

<p align="center">
  <img src="https://petewarden.files.wordpress.com/2015/04/gemm_corrected.png" alt="matrix-multiplication-image" height="250px" width="600px"></img>
</p>

This implementation provides fast matrix multiplication for multiplying two square matrices. This method is known as the general matrix multiplication (GEMM). Many scientific computing libraries like Numpy, BLAS, etc., use a slight modified version of this algorithm. This implementation works only on square matrices. This is done to avoid making the algorithm too complicated to handle rectangular matrices. 

This implementation deals with multiplying two sqaured matrices ordered in column major order. In Linear Algebra you order everything according to columns. Hence we will also order it column wise. The two square matrices must have dimensions that is divisible by 4. This is because we are using a 4x4 kernel to compute the dot products of sub matrices. 

## License

MIT
