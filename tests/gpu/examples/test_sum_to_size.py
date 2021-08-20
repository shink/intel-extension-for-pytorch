import torch
import torch.nn as nn
import torch.nn.functional as F
from torch.testing._internal.common_utils import TestCase
import ipex
import os
import copy
import pytest

cpu_device = torch.device("cpu")
xpu_device = torch.device("xpu")

class TestNNMethod(TestCase):
    def test_sum_to_list(self, dtype=torch.float):
        x_cpu = torch.randn(6, 8)
        x_xpu = x_cpu.to(xpu_device)
        
        # sum_to_size, keep second dim
        x_cpu_sum = x_cpu.sum_to_size(1, 8)
        x_xpu_sum = x_xpu.sum_to_size(1, 8)

        print('x_cpu_sum = ', x_cpu_sum)
        print('x_xpu_sum = ', x_xpu_sum.to(cpu_device))

        self.assertEqual(x_cpu_sum, x_xpu_sum.to(cpu_device))

        # sum_to_size, keep first dim
        x_cpu_sum = x_cpu.sum_to_size(6, 1)
        x_xpu_sum = x_xpu.sum_to_size(6, 1)

        print('x_cpu_sum = ', x_cpu_sum)
        print('x_xpu_sum = ', x_xpu_sum.to(cpu_device))

        self.assertEqual(x_cpu_sum, x_xpu_sum.to(cpu_device))