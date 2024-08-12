# LLM Optimization Overview

Here you can find benchmarking scripts for large language models (LLM) text generation. These scripts:

- Support Llama 2, GPT-J, Qwen, OPT, Bloom model families and some other Chinese models such as ChatGLMv3-6B and Baichuan2-13B. 
- Include both single instance and distributed (DeepSpeed) use cases for FP16 optimization.
- Cover model generation inference with low precision cases for different models with best performance and accuracy (fp16 AMP and weight only quantization)

## Environment Setup

### [Recommended] Docker-based environment setup with compilation from source

```bash
# Get the Intel® Extension for PyTorch* source code
git clone https://github.com/intel/intel-extension-for-pytorch.git
cd intel-extension-for-pytorch
git checkout xpu-main
git submodule sync
git submodule update --init --recursive

# Build an image with the provided Dockerfile by compiling Intel® Extension for PyTorch* from source
docker build -f examples/gpu/llm/Dockerfile --build-arg COMPILE=ON -t ipex-llm:main .

# Run the container with command below
docker run -it --rm --privileged -v /dev/dri/by-path:/dev/dri/by-path ipex-llm:main bash

# When the command prompt shows inside the docker container, enter llm examples directory
cd llm

# Activate environment variables
source ./tools/env_activate.sh [inference|fine-tuning]
```

### Conda-based environment setup with compilation from source

Make sure the driver and Base Toolkit are installed without using a docker container. Refer to [Installation Guide](https://intel.github.io/intel-extension-for-pytorch/#installation?platform=gpu&version=v2.1.40%2Bxpu&os=linux%2Fwsl2&package=source).

```bash

# Get the Intel® Extension for PyTorch* source code
git clone https://github.com/intel/intel-extension-for-pytorch.git
cd intel-extension-for-pytorch
git checkout xpu-main
git submodule sync
git submodule update --init --recursive

# Make sure you have GCC >= 11 is installed on your system.
# Create a conda environment
conda create -n llm python=3.10 -y
conda activate llm
# Setup the environment with the provided script
cd examples/gpu/llm
# If you want to install Intel® Extension for PyTorch\* from source, use the commands below:
bash ./tools/env_setup.sh 3 <DPCPP_ROOT> <ONEMKL_ROOT> <ONECCL_ROOT> <MPI_ROOT> <AOT>
conda deactivate
conda activate llm
source ./tools/env_activate.sh [inference|fine-tuning]
```

where <br />
- `AOT` is a text string to enable `Ahead-Of-Time` compilation for specific GPU models. Check [tutorial](../../../../../docs/tutorials/technical_details/AOT.md) for details.<br />

<br />
 
## How To Run LLM with ipex.llm

Inference and fine-tuning are supported in individual directories.

For inference example scripts, visit the [inference](./inference/) directory.

For fine-tuning example scripts, visit the [fine-tuning](./fine-tuning/) directory.