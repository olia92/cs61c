relu_forward:
    189, Generating NVIDIA GPU code
        191, #pragma acc loop gang, vector(128) collapse(3) /* blockIdx.x threadIdx.x */
        192,   /* blockIdx.x threadIdx.x collapsed */
        193,   /* blockIdx.x threadIdx.x collapsed */
    189, Generating implicit copy(inputs[i],outputs[i]) [if not already present]
         Generating implicit copyin(l) [if not already present]