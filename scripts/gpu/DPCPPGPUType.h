#pragma once

// @generated by aten/src/ATen/gen.py

#include <c10/core/TensorOptions.h>
#include <c10/core/Scalar.h>
#include <c10/core/QScheme.h>
#include <c10/core/MemoryFormat.h>
#include <c10/util/ArrayRef.h>
#include <c10/util/intrusive_ptr.h>
#include <torch/csrc/WindowsTorchApiMacro.h>

#include <ATen/DeviceGuard.h>

namespace c10 {
struct Storage;
}

namespace at {

class Tensor;
using TensorList = ArrayRef<Tensor>;

class Context;
struct Generator;

struct Quantizer;
// This is temporary typedef to enable Quantizer in aten native function API
// we'll remove them when we are actually exposing Quantizer class
// to frontend
using ConstQuantizerPtr = const c10::intrusive_ptr<Quantizer>&;

struct TORCH_API SYCLType final {
  // static std::tuple<Tensor,Tensor,Tensor,std::vector<Tensor>> _sycl_rnn(const Tensor & self, const Tensor & hx_, const Tensor & cx_, TensorList params, bool has_biases, int64_t num_layers_, double dropout_p, bool train, bool bidirectional, bool batch_first);
  // static std::tuple<Tensor,Tensor,Tensor,std::vector<Tensor>> _sycl_rnn_backward(const Tensor & self, const Tensor & hx_, const Tensor & cx_, const Tensor & output, const Tensor & hy_, const Tensor & cy_, TensorList workspace, const Tensor & grad_output, const Tensor & grad_hy, const Tensor & grad_cy, TensorList params, bool has_biases, int64_t num_layers_, double dropout_p, bool train, bool bidirectional, bool batch_first);
  // static Tensor addmv(const Tensor & self, const Tensor & mat, const Tensor & vec, Scalar beta, Scalar alpha);
  // static Tensor & addmv_(Tensor & self, const Tensor & mat, const Tensor & vec, Scalar beta, Scalar alpha);
  // static Tensor & addmv_out(Tensor & out, const Tensor & self, const Tensor & mat, const Tensor & vec, Scalar beta, Scalar alpha);
   static Tensor & arange_out(Tensor & out, Scalar start, Scalar end, Scalar step);  // aten::arange.start_out(Scalar start, Scalar end, Scalar step=1, *, Tensor(a!) out) -> Tensor(a!)
  static Tensor as_strided(const Tensor & self, IntArrayRef size, IntArrayRef stride, c10::optional<int64_t> storage_offset); // aten::as_strided(Tensor(a) self, int[] size, int[] stride, int? storage_offset=None) -> Tensor(a)
  static Tensor & atan_(Tensor & self); // aten::atan_(Tensor(a!) self) -> Tensor(a!)
  // static Tensor baddbmm(const Tensor & self, const Tensor & batch1, const Tensor & batch2, Scalar beta, Scalar alpha);
  // static Tensor & baddbmm_(Tensor & self, const Tensor & batch1, const Tensor & batch2, Scalar beta, Scalar alpha);
  // static Tensor & baddbmm_out(Tensor & out, const Tensor & self, const Tensor & batch1, const Tensor & batch2, Scalar beta, Scalar alpha);
  // static Tensor & bernoulli_(Tensor & self, const Tensor & p, Generator * generator); // aten::bernoulli_.Tensor(Tensor(a!) self, Tensor p, *, Generator? generator=None) -> Tensor(a!)
  // static Tensor & bernoulli_(Tensor & self, double p, Generator * generator); // aten::bernoulli_.float(Tensor(a!) self, float p=0.5, *, Generator? generator=None) -> Tensor(a!)
  // static Tensor bincount(const Tensor & self, const Tensor & weights, int64_t minlength);
  // static Tensor & logical_xor_out(Tensor & out, const Tensor & self, const Tensor & other);
  // static Tensor bmm(const Tensor & self, const Tensor & mat2);
  // static Tensor & bmm_out(Tensor & out, const Tensor & self, const Tensor & mat2);
  static Tensor & clamp_(Tensor & self, c10::optional<Scalar> min, c10::optional<Scalar> max); // aten::clamp_(Tensor(a!) self, Scalar? min=None, Scalar? max=None) -> Tensor(a!)
  static Tensor & clamp_out(Tensor & out, const Tensor & self, c10::optional<Scalar> min, c10::optional<Scalar> max); // aten::clamp.out(Tensor self, Scalar? min=None, Scalar? max=None, *, Tensor(a!) out) -> Tensor(a!)
  static Tensor & clamp_max_(Tensor & self, Scalar max); // aten::clamp_max_(Tensor(a!) self, Scalar max) -> Tensor(a!)
  static Tensor & clamp_max_out(Tensor & out, const Tensor & self, Scalar max); // aten::clamp_max.out(Tensor self, Scalar max, *, Tensor(a!) out) -> Tensor(a!)
  static Tensor & clamp_min_(Tensor & self, Scalar min); // aten::clamp_min_(Tensor(a!) self, Scalar min) -> Tensor(a!)
  static Tensor & clamp_min_out(Tensor & out, const Tensor & self, Scalar min); // aten::clamp_min.out(Tensor self, Scalar min, *, Tensor(a!) out) -> Tensor(a!)
  static Tensor embedding_dense_backward(const Tensor & grad_output, const Tensor & indices, int64_t num_weights, int64_t padding_idx, bool scale_grad_by_freq); // aten::embedding_dense_backward(Tensor grad_output, Tensor indices, int num_weights, int padding_idx, bool scale_grad_by_freq) -> Tensor
  static std::tuple<Tensor,Tensor,Tensor,Tensor> _embedding_bag(const Tensor & weight, const Tensor & indices, const Tensor & offsets, bool scale_grad_by_freq, int64_t mode, bool sparse, const Tensor & per_sample_weights); // aten::_embedding_bag(Tensor weight, Tensor indices, Tensor offsets, bool scale_grad_by_freq=False, int mode=0, bool sparse=False, Tensor? per_sample_weights=None) -> (Tensor, Tensor, Tensor, Tensor)
  static Tensor _embedding_bag_dense_backward(const Tensor & grad, const Tensor & indices, const Tensor & offsets, const Tensor & offset2bag, const Tensor & bag_size, const Tensor & maximum_indices, int64_t num_weights, bool scale_grad_by_freq, int64_t mode, const Tensor & per_sample_weights); // aten::_embedding_bag_dense_backward(Tensor grad, Tensor indices, Tensor offsets, Tensor offset2bag, Tensor bag_size, Tensor maximum_indices, int num_weights, bool scale_grad_by_freq, int mode, Tensor? per_sample_weights) -> Tensor
  static Tensor empty(IntArrayRef size, const TensorOptions & options, c10::optional<MemoryFormat> memory_format); // aten::empty.memory_format(int[] size, *, ScalarType? dtype=None, Layout? layout=None, Device? device=None, bool? pin_memory=None, MemoryFormat? memory_format=None) -> Tensor
  static Tensor & resize_(Tensor & self, IntArrayRef size, c10::optional<MemoryFormat> memory_format); // aten::resize_(Tensor(a!) self, int[] size, *, MemoryFormat? memory_format=None) -> Tensor(a!)
   static Tensor empty_strided(IntArrayRef size, IntArrayRef stride, const TensorOptions & options);  // aten::empty_strided(int[] size, int[] stride, *, ScalarType? dtype=None, Layout? layout=None, Device? device=None, bool? pin_memory=None) -> Tensor
  static Tensor & erf_(Tensor & self); // aten::erf_(Tensor(a!) self) -> Tensor(a!)
  static Tensor & erfc_(Tensor & self); // aten::erfc_(Tensor(a!) self) -> Tensor(a!)
  static Tensor & exp_(Tensor & self); // aten::exp_(Tensor(a!) self) -> Tensor(a!)
  static Tensor & eye_out(Tensor & out, int64_t n); // aten::eye.out(int n, *, Tensor(a!) out) -> Tensor(a!)
  static Tensor & eye_out(Tensor & out, int64_t n, int64_t m); // aten::eye.m_out(int n, int m, *, Tensor(a!) out) -> Tensor(a!)
  static std::tuple<Tensor &,Tensor &> kthvalue_out(Tensor & values, Tensor & indices, const Tensor & self, int64_t k, int64_t dim, bool keepdim); // aten::kthvalue.values(Tensor self, int k, int dim=-1, bool keepdim=False, *, Tensor(a!) values, Tensor(b!) indices) -> (Tensor(a!) values, Tensor(b!) indices)
  static Tensor & linspace_out(Tensor & out, Scalar start, Scalar end, int64_t steps);  // aten::linspace.out(Scalar start, Scalar end, int steps=100, *, Tensor(a!) out) -> Tensor(a!)
  static Tensor & logspace_out(Tensor & out, Scalar start, Scalar end, int64_t steps, double base);  // aten::logspace.out(Scalar start, Scalar end, int steps=100, float base=10.0, *, Tensor(a!) out) -> Tensor(a!)
  static Tensor _log_softmax(const Tensor & self, int64_t dim, bool half_to_float); // aten::_log_softmax(Tensor self, int dim, bool half_to_float) -> Tensor
  static Tensor _log_softmax_backward_data(const Tensor & grad_output, const Tensor & output, int64_t dim, const Tensor & self); // aten::_log_softmax_backward_data(Tensor grad_output, Tensor output, int dim, Tensor self) -> Tensor
  static Tensor mm(const Tensor & self, const Tensor & mat2); // aten::mm(Tensor self, Tensor mat2) -> Tensor
  static Tensor & mm_out(Tensor & out, const Tensor & self, const Tensor & mat2); // aten::mm.out(Tensor self, Tensor mat2, *, Tensor(a!) out) -> Tensor(a!)
  static Tensor narrow_copy(const Tensor & self, int64_t dim, int64_t start, int64_t length); // aten::narrow_copy(Tensor self, int dim, int start, int length) -> Tensor
  static std::tuple<Tensor,Tensor,Tensor> native_batch_norm(const Tensor & input, const Tensor & weight, const Tensor & bias, const Tensor & running_mean, const Tensor & running_var, bool training, double momentum, double eps); // aten::native_batch_norm(Tensor input, Tensor? weight, Tensor? bias, Tensor? running_mean, Tensor? running_var, bool training, float momentum, float eps) -> (Tensor, Tensor, Tensor)
  static std::tuple<Tensor,Tensor,Tensor> native_batch_norm_backward(const Tensor & grad_out, const Tensor & input, const Tensor & weight, const Tensor & running_mean, const Tensor & running_var, const Tensor & save_mean, const Tensor & save_invstd, bool train, double eps, std::array<bool,3> output_mask); // aten::native_batch_norm_backward(Tensor grad_out, Tensor input, Tensor? weight, Tensor? running_mean, Tensor? running_var, Tensor? save_mean, Tensor? save_invstd, bool train, float eps, bool[3] output_mask) -> (Tensor, Tensor, Tensor)
  static Tensor & range_out(Tensor & out, Scalar start, Scalar end, Scalar step);  // aten::range.out(Scalar start, Scalar end, Scalar step=1, *, Tensor(a!) out) -> Tensor(a!)
  // static Tensor repeat_interleave(const Tensor & repeats); // aten::repeat_interleave.Tensor(Tensor repeats) -> Tensor
  // static Tensor relu(const Tensor & self);
  static Tensor & relu_(Tensor & self); // aten::relu_(Tensor(a!) self) -> Tensor(a!)
  static Tensor & rsqrt_out(Tensor & out, const Tensor & self); // aten::rsqrt.out(Tensor self, *, Tensor(a!) out) -> Tensor(a!)
  static Tensor sigmoid(const Tensor & self); // aten::sigmoid(Tensor self) -> Tensor
  static Tensor & sigmoid_(Tensor & self); // aten::sigmoid_(Tensor(a!) self) -> Tensor(a!)
  static Tensor & sigmoid_out(Tensor & out, const Tensor & self); // aten::sigmoid.out(Tensor self, *, Tensor(a!) out) -> Tensor(a!)
  static Tensor _softmax(const Tensor & self, int64_t dim, bool half_to_float); // aten::_softmax(Tensor self, int dim, bool half_to_float) -> Tensor
  static Tensor _softmax_backward_data(const Tensor & grad_output, const Tensor & output, int64_t dim, const Tensor & self); // aten::_softmax_backward_data(Tensor grad_output, Tensor output, int dim, Tensor self) -> Tensor
  static Tensor & sqrt_out(Tensor & out, const Tensor & self); // aten::sqrt.out(Tensor self, *, Tensor(a!) out) -> Tensor(a!)
  static Tensor & tan_(Tensor & self); // aten::tan_(Tensor(a!) self) -> Tensor(a!)
  static Tensor & tanh_(Tensor & self); // aten::tanh_(Tensor(a!) self) -> Tensor(a!)
  static Tensor roll(const Tensor & self, IntArrayRef shifts, IntArrayRef dims); // aten::roll(Tensor self, int[1] shifts, int[1] dims=[]) -> Tensor
  // static Tensor _s_where(const Tensor & condition, const Tensor & self, const Tensor & other);
  static Tensor clone(const Tensor & self, c10::optional<MemoryFormat> memory_format); // aten::clone(Tensor self, *, MemoryFormat? memory_format=None) -> Tensor
  static Tensor & resize_as_(Tensor & self, const Tensor & the_template, c10::optional<MemoryFormat> memory_format); // aten::resize_as_(Tensor(a!) self, Tensor the_template, *, int? memory_format=None) -> (Tensor(a!))
  static Tensor & zero_(Tensor & self); // aten::zero_(Tensor(a!) self) -> Tensor(a!)
  static Scalar _local_scalar_dense(const Tensor & self); // aten::_local_scalar_dense(Tensor self) -> Scalar
  static Tensor & set_(Tensor & self, Storage source); // aten::set_.source_Storage(Tensor(a!) self, Storage source) -> Tensor(a!)
  static Tensor & set_(Tensor & self, Storage source, int64_t storage_offset, IntArrayRef size, IntArrayRef stride); // aten::set_.source_Storage_storage_offset(Tensor(a!) self, Storage source, int storage_offset, int[] size, int[] stride=[]) -> Tensor(a!)
  static Tensor & set_(Tensor & self, const Tensor & source); // aten::set_.source_Tensor(Tensor(a!) self, Tensor source) -> Tensor(a!)
  static Tensor & set_(Tensor & self); // aten::set_(Tensor(a!) self) -> Tensor(a!)
  // static bool is_set_to(const Tensor & self, const Tensor & tensor);
  // static Tensor & masked_fill_(Tensor & self, const Tensor & mask, Scalar value);
  // static Tensor & masked_fill_(Tensor & self, const Tensor & mask, const Tensor & value);
  // static Tensor & masked_scatter_(Tensor & self, const Tensor & mask, const Tensor & source);
  static Tensor view(const Tensor & self, IntArrayRef size); // aten::view(Tensor(a) self, int[] size) -> Tensor(a)
  static Tensor & index_add_(Tensor & self, int64_t dim, const Tensor & index, const Tensor & source); // aten::index_add_(Tensor(a!) self, int dim, Tensor index, Tensor source) -> Tensor(a!)
  static Tensor & index_fill_(Tensor & self, int64_t dim, const Tensor & index, Scalar value); // aten::index_fill_.int_Scalar(Tensor(a!) self, int dim, Tensor index, Scalar value) -> Tensor(a!)
  static Tensor & index_fill_(Tensor & self, int64_t dim, const Tensor & index, const Tensor & value); // aten::index_fill_.int_Tensor(Tensor(a!) self, int dim, Tensor index, Tensor value) -> Tensor(a!)
  // static Tensor & scatter_(Tensor & self, int64_t dim, const Tensor & index, const Tensor & src);
  // static Tensor & scatter_(Tensor & self, int64_t dim, const Tensor & index, Scalar value);
  // static Tensor & scatter_add_(Tensor & self, int64_t dim, const Tensor & index, const Tensor & src);
  static Tensor __and__(const Tensor & self, Scalar other); // aten::__and__.Scalar(Tensor self, Scalar other) -> Tensor
  static Tensor __and__(const Tensor & self, const Tensor & other); // aten::__and__.Tensor(Tensor self, Tensor other) -> Tensor
  static Tensor & __iand__(Tensor & self, Scalar other); // aten::__iand__.Scalar(Tensor(a!) self, Scalar other) -> Tensor(a!)
  static Tensor & __iand__(Tensor & self, const Tensor & other); // aten::__iand__.Tensor(Tensor(a!) self, Tensor other) -> Tensor(a!)
  static Tensor __or__(const Tensor & self, Scalar other); // aten::__or__.Scalar(Tensor self, Scalar other) -> Tensor
  static Tensor __or__(const Tensor & self, const Tensor & other); // aten::__or__.Tensor(Tensor self, Tensor other) -> Tensor
  static Tensor & __ior__(Tensor & self, Scalar other); // aten::__ior__.Scalar(Tensor(a!) self, Scalar other) -> Tensor(a!)
  static Tensor & __ior__(Tensor & self, const Tensor & other); // aten::__ior__.Tensor(Tensor(a!) self, Tensor other) -> Tensor(a!)
  static Tensor & tril_(Tensor & self, int64_t diagonal); // aten::tril_(Tensor(a!) self, int diagonal=0) -> Tensor(a!)
  static Tensor & triu_(Tensor & self, int64_t diagonal); // aten::triu_(Tensor(a!) self, int diagonal=0) -> Tensor(a!)
  static Tensor & erfinv_(Tensor & self); // aten::erfinv_(Tensor(a!) self) -> Tensor(a!)
  static Tensor & fmod_(Tensor & self, Scalar other); // aten::fmod_.Scalar(Tensor(a!) self, Scalar other) -> Tensor(a!)
  static Tensor & fmod_(Tensor & self, const Tensor & other); // aten::fmod_.Tensor(Tensor(a!) self, Tensor other) -> Tensor(a!)
  static Tensor & remainder_(Tensor & self, Scalar other); // aten::remainder_.Scalar(Tensor(a!) self, Scalar other) -> Tensor(a!)
  static Tensor & remainder_(Tensor & self, const Tensor & other); // aten::remainder_.Tensor(Tensor(a!) self, Tensor other) -> Tensor(a!)
  // static Tensor & addbmm_(Tensor & self, const Tensor & batch1, const Tensor & batch2, Scalar beta, Scalar alpha);
  // static Tensor & addbmm_out(Tensor & out, const Tensor & self, const Tensor & batch1, const Tensor & batch2, Scalar beta, Scalar alpha);
  // static Tensor addbmm(const Tensor & self, const Tensor & batch1, const Tensor & batch2, Scalar beta, Scalar alpha);
  static Tensor & normal_(Tensor & self, double mean, double std, Generator * generator); // aten::normal_(Tensor(a!) self, float mean=0, float std=1, *, Generator? generator=None) -> Tensor(a!)
  // static Tensor & diag_out(Tensor & out, const Tensor & self, int64_t diagonal);
  // static Tensor diag(const Tensor & self, int64_t diagonal);
   static Tensor & triu_out(Tensor & out, const Tensor & self, int64_t diagonal); // aten::triu.out(Tensor self, int diagonal=0, *, Tensor(a!) out) -> Tensor(a!)
   static Tensor & tril_out(Tensor & out, const Tensor & self, int64_t diagonal); // aten::tril.out(Tensor self, int diagonal=0, *, Tensor(a!) out) -> Tensor(a!)
   static Tensor tril_indices(int64_t row, int64_t col, int64_t offset, const TensorOptions & options); // aten::tril_indices(int row, int col, int offset=0, *, ScalarType? dtype=long, Layout? layout=None, Device? device=None, bool? pin_memory=None) -> Tensor
   static Tensor triu_indices(int64_t row, int64_t col, int64_t offset, const TensorOptions & options); // aten::triu_indices(int row, int col, int offset=0, *, ScalarType? dtype=long, Layout? layout=None, Device? device=None, bool? pin_memory=None) -> Tensor
  // static Tensor trace(const Tensor & self);
  static Tensor & ne_out(Tensor & out, const Tensor & self, Scalar other); // aten::ne.Scalar_out(Tensor self, Scalar other, *, Tensor(a!) out) -> Tensor(a!)
  static Tensor ne(const Tensor & self, Scalar other); // aten::ne.Scalar(Tensor self, Scalar other) -> Tensor
  static Tensor ne(const Tensor & self, const Tensor & other); // aten::ne.Tensor(Tensor self, Tensor other) -> Tensor
  static Tensor & eq_out(Tensor & out, const Tensor & self, Scalar other); // aten::eq.Scalar_out(Tensor self, Scalar other, *, Tensor(a!) out) -> Tensor(a!)
  static Tensor eq(const Tensor & self, Scalar other); // aten::eq.Scalar(Tensor self, Scalar other) -> Tensor
  static Tensor eq(const Tensor & self, const Tensor & other); // aten::eq.Tensor(Tensor self, Tensor other) -> Tensor
  static Tensor & ge_out(Tensor & out, const Tensor & self, Scalar other); // aten::ge.Scalar_out(Tensor self, Scalar other, *, Tensor(a!) out) -> Tensor(a!)
  static Tensor ge(const Tensor & self, Scalar other); // aten::ge.Scalar(Tensor self, Scalar other) -> Tensor
  static Tensor ge(const Tensor & self, const Tensor & other); // aten::ge.Tensor(Tensor self, Tensor other) -> Tensor
  static Tensor & le_out(Tensor & out, const Tensor & self, Scalar other); // aten::le.Scalar_out(Tensor self, Scalar other, *, Tensor(a!) out) -> Tensor(a!)
  static Tensor le(const Tensor & self, Scalar other); // aten::le.Scalar(Tensor self, Scalar other) -> Tensor
  static Tensor le(const Tensor & self, const Tensor & other); // aten::le.Tensor(Tensor self, Tensor other) -> Tensor
  static Tensor & gt_out(Tensor & out, const Tensor & self, Scalar other); // aten::gt.Scalar_out(Tensor self, Scalar other, *, Tensor(a!) out) -> Tensor(a!)
  static Tensor gt(const Tensor & self, Scalar other); // aten::gt.Scalar(Tensor self, Scalar other) -> Tensor
  static Tensor gt(const Tensor & self, const Tensor & other); // aten::gt.Tensor(Tensor self, Tensor other) -> Tensor
  static Tensor & lt_out(Tensor & out, const Tensor & self, Scalar other); // aten::lt.Scalar_out(Tensor self, Scalar other, *, Tensor(a!) out) -> Tensor(a!)
  static Tensor lt(const Tensor & self, Scalar other); // aten::lt.Scalar(Tensor self, Scalar other) -> Tensor
  static Tensor lt(const Tensor & self, const Tensor & other); // aten::lt.Tensor(Tensor self, Tensor other) -> Tensor
  // static Tensor & take_out(Tensor & out, const Tensor & self, const Tensor & index);
  // static Tensor take(const Tensor & self, const Tensor & index);
  static Tensor & index_select_out(Tensor & out, const Tensor & self, int64_t dim, const Tensor & index); // aten::index_select.out(Tensor self, int dim, Tensor index, *, Tensor(a!) out) -> Tensor(a!)
  static Tensor index_select(const Tensor & self, int64_t dim, const Tensor & index); // aten::index_select(Tensor self, int dim, Tensor index) -> Tensor
  // static Tensor & masked_select_out(Tensor & out, const Tensor & self, const Tensor & mask);
  // static Tensor masked_select(const Tensor & self, const Tensor & mask);
  static Tensor & nonzero_out(Tensor & out, const Tensor & self); // aten::nonzero.out(Tensor self, *, Tensor(a!) out) -> Tensor(a!)
  static Tensor nonzero(const Tensor & self); // aten::nonzero(Tensor self) -> Tensor
  // static Tensor & gather_out(Tensor & out, const Tensor & self, int64_t dim, const Tensor & index, bool sparse_grad);
  // static Tensor gather(const Tensor & self, int64_t dim, const Tensor & index, bool sparse_grad);
  static Tensor & erfinv_out(Tensor & out, const Tensor & self); // aten::erfinv.out(Tensor self, *, Tensor(a!) out) -> Tensor(a!)
  static Tensor erfinv(const Tensor & self); // aten::erfinv(Tensor self) -> Tensor
  static Tensor sign(const Tensor & self); // aten::sign(Tensor self) -> Tensor
  static Tensor & sign_(Tensor & self); // aten::sign_(Tensor(a!) self) -> Tensor(a!)
  static Tensor & sign_out(Tensor & out, const Tensor & self); // aten::sign.out(Tensor self, *, Tensor(a!) out) -> Tensor(a!)
  static Tensor & fmod_out(Tensor & out, const Tensor & self, Scalar other); // aten::fmod.Scalar_out(Tensor self, Scalar other, *, Tensor(a!) out) -> Tensor(a!)
  static Tensor fmod(const Tensor & self, Scalar other); // aten::fmod.Scalar(Tensor self, Scalar other) -> Tensor
  static Tensor & fmod_out(Tensor & out, const Tensor & self, const Tensor & other); // aten::fmod.Tensor_out(Tensor self, Tensor other, *, Tensor(a!) out) -> Tensor(a!)
  static Tensor fmod(const Tensor & self, const Tensor & other); // aten::fmod.Tensor(Tensor self, Tensor other) -> Tensor
  static Tensor & remainder_out(Tensor & out, const Tensor & self, Scalar other); // aten::remainder.Scalar_out(Tensor self, Scalar other, *, Tensor(a!) out) -> Tensor(a!)
  static Tensor remainder(const Tensor & self, Scalar other); // aten::remainder.Scalar(Tensor self, Scalar other) -> Tensor
  static Tensor & remainder_out(Tensor & out, const Tensor & self, const Tensor & other); // aten::remainder.Tensor_out(Tensor self, Tensor other, *, Tensor(a!) out) -> Tensor(a!)
  static Tensor remainder(const Tensor & self, const Tensor & other); // aten::remainder.Tensor(Tensor self, Tensor other) -> Tensor
  static Tensor & min_out(Tensor & out, const Tensor & self, const Tensor & other); // aten::min.out(Tensor self, Tensor other, *, Tensor(a!) out) -> Tensor(a!)
  static Tensor min(const Tensor & self, const Tensor & other); // aten::min.other(Tensor self, Tensor other) -> Tensor
  static Tensor min(const Tensor & self); // aten::min(Tensor self) -> Tensor
  static Tensor & max_out(Tensor & out, const Tensor & self, const Tensor & other); // aten::max.out(Tensor self, Tensor other, *, Tensor(a!) out) -> Tensor(a!)
  static Tensor max(const Tensor & self, const Tensor & other); // aten::max.other(Tensor self, Tensor other) -> Tensor
  static Tensor max(const Tensor & self); // aten::max(Tensor self) -> Tensor
  static Tensor median(const Tensor & self); // aten::median(Tensor self) -> Tensor
  static std::tuple<Tensor &,Tensor &> sort_out(Tensor & values, Tensor & indices, const Tensor & self, int64_t dim, bool descending); // aten::sort.values(Tensor self, int dim=-1, bool descending=False, *, Tensor(a!) values, Tensor(b!) indices) -> (Tensor(a!) values, Tensor(b!) indices)
  static std::tuple<Tensor,Tensor> sort(const Tensor & self, int64_t dim, bool descending); // aten::sort(Tensor self, int dim=-1, bool descending=False) -> (Tensor values, Tensor indices)
  static std::tuple<Tensor &,Tensor &> topk_out(Tensor & values, Tensor & indices, const Tensor & self, int64_t k, int64_t dim, bool largest, bool sorted); // aten::topk.values(Tensor self, int k, int dim=-1, bool largest=True, bool sorted=True, *, Tensor(a!) values, Tensor(b!) indices) ->(Tensor(a!) values, Tensor(b!) indices)
  static std::tuple<Tensor,Tensor> topk(const Tensor & self, int64_t k, int64_t dim, bool largest, bool sorted); // aten::topk(Tensor self, int k, int dim=-1, bool largest=True, bool sorted=True) -> (Tensor values, Tensor indices)
  static Tensor unfold(const Tensor & self, int64_t dimension, int64_t size, int64_t step); // aten::unfold(Tensor(a) self, int dimension, int size, int step) -> Tensor(a)
  static Tensor pow(const Tensor & self, Scalar exponent); // aten::pow.Tensor_Scalar(Tensor self, Scalar exponent) -> Tensor
  static Tensor & pow_out(Tensor & out, const Tensor & self, Scalar exponent); // aten::pow.Tensor_Scalar_out(Tensor self, Scalar exponent, *, Tensor(a!) out) -> Tensor(a!)
  static Tensor pow(const Tensor & self, const Tensor & exponent); // aten::pow.Tensor_Tensor(Tensor self, Tensor exponent) -> Tensor
  static Tensor & pow_out(Tensor & out, const Tensor & self, const Tensor & exponent); // aten::pow.Tensor_Tensor_out(Tensor self, Tensor exponent, *, Tensor(a!) out) -> Tensor(a!)
  static Tensor pow(Scalar self, const Tensor & exponent); // aten::pow.Scalar(Scalar self, Tensor exponent) -> Tensor
  static Tensor & pow_out(Tensor & out, Scalar self, const Tensor & exponent); // aten::pow.Scalar_out(Scalar self, Tensor exponent, *, Tensor(a!) out) -> Tensor(a!)
  static Tensor & pow_(Tensor & self, Scalar exponent); // aten::pow_.Scalar(Tensor(a!) self, Scalar exponent) -> Tensor(a!)
  static Tensor & pow_(Tensor & self, const Tensor & exponent); // aten::pow_.Tensor(Tensor(a!) self, Tensor exponent) -> Tensor(a!)
  static Tensor _cumsum(const Tensor & self, int64_t dim); // aten::_cumsum(Tensor self, int dim) -> Tensor
  static Tensor & _cumsum_out(Tensor & out, const Tensor & self, int64_t dim); // aten::_cumsum.out(Tensor self, int dim, *, Tensor(a!) out) -> Tensor(a!)
  static Tensor _cumprod(const Tensor & self, int64_t dim); // aten::_cumprod(Tensor self, int dim) -> Tensor
  static Tensor & _cumprod_out(Tensor & out, const Tensor & self, int64_t dim); // aten::_cumprod.out(Tensor self, int dim, *, Tensor(a!) out) -> Tensor(a!)
  static Tensor addmm(const Tensor & self, const Tensor & mat1, const Tensor & mat2, Scalar beta, Scalar alpha); // aten::addmm(Tensor self, Tensor mat1, Tensor mat2, *, Scalar beta=1, Scalar alpha=1) -> Tensor
  static Tensor _cat(TensorList tensors, int64_t dim); // aten::_cat(Tensor[] tensors, int dim=0) -> Tensor
  static Tensor & _cat_out(Tensor & out, TensorList tensors, int64_t dim); // aten::_cat.out(Tensor[] tensors, int dim=0, *, Tensor(a!) out) -> Tensor(a!)
  static std::tuple<Tensor,Tensor> max(const Tensor & self, int64_t dim, bool keepdim); // aten::max.dim(Tensor self, int dim, bool keepdim=False) -> (Tensor values, Tensor indices)
  static std::tuple<Tensor &,Tensor &> max_out(Tensor & max, Tensor & max_values, const Tensor & self, int64_t dim, bool keepdim); // aten::max.dim_max(Tensor self, int dim, bool keepdim=False, *, Tensor(a!) max, Tensor(b!) max_values) -> (Tensor(a!) values, Tensor(b!) indices)
  static std::tuple<Tensor,Tensor> _max(const Tensor & self, int64_t dim, bool keepdim); // aten::_max(Tensor self, int dim, bool keepdim=False) -> (Tensor, Tensor)
  static std::tuple<Tensor &,Tensor &> _max_out(Tensor & max, Tensor & max_indices, const Tensor & self, int64_t dim, bool keepdim); // aten::_max.max(Tensor self, int dim, bool keepdim=False, *, Tensor(a!) max, Tensor(b!) max_indices) -> (Tensor(a!), Tensor(b!))
  static std::tuple<Tensor,Tensor> min(const Tensor & self, int64_t dim, bool keepdim); // aten::min.dim(Tensor self, int dim, bool keepdim=False) -> (Tensor values, Tensor indices)
  static std::tuple<Tensor &,Tensor &> min_out(Tensor & min, Tensor & min_indices, const Tensor & self, int64_t dim, bool keepdim); // aten::min.dim_min(Tensor self, int dim, bool keepdim=False, *, Tensor(a!) min, Tensor(b!) min_indices) -> (Tensor(a!) values, Tensor(b!) indices)
  static std::tuple<Tensor,Tensor> _min(const Tensor & self, int64_t dim, bool keepdim); // aten::_min(Tensor self, int dim, bool keepdim=False) -> (Tensor, Tensor)
  static std::tuple<Tensor &,Tensor &> _min_out(Tensor & min, Tensor & min_indices, const Tensor & self, int64_t dim, bool keepdim); // aten::_min.min(Tensor self, int dim, bool keepdim=False, *, Tensor(a!) min, Tensor(b!) min_indices) -> (Tensor(a!), Tensor(b!))
  static Tensor & binary_cross_entropy_out(Tensor & out, const Tensor & self, const Tensor & target, const Tensor & weight, int64_t reduction); // aten::binary_cross_entropy.out(Tensor self, Tensor target, Tensor? weight=None, int reduction=Mean, *, Tensor(a!) out) -> Tensor(a!)
  static Tensor binary_cross_entropy(const Tensor & self, const Tensor & target, const Tensor & weight, int64_t reduction); // aten::binary_cross_entropy(Tensor self, Tensor target, Tensor? weight=None, int reduction=Mean) -> Tensor
  static Tensor & binary_cross_entropy_backward_out(Tensor & grad_input, const Tensor & grad_output, const Tensor & self, const Tensor & target, const Tensor & weight, int64_t reduction); // aten::binary_cross_entropy_backward.grad_input(Tensor grad_output, Tensor self, Tensor target, Tensor? weight=None, int reduction=Mean, *, Tensor(a!) grad_input) -> Tensor(a!)
  static Tensor binary_cross_entropy_backward(const Tensor & grad_output, const Tensor & self, const Tensor & target, const Tensor & weight, int64_t reduction); // aten::binary_cross_entropy_backward(Tensor grad_output, Tensor self, Tensor target, Tensor? weight=None, int reduction=Mean) -> Tensor
  static Tensor & mse_loss_out(Tensor & out, const Tensor & self, const Tensor & target, int64_t reduction); // aten::mse_loss.out(Tensor self, Tensor target, int reduction=Mean, *, Tensor(a!) out) -> Tensor(a!)
  static Tensor mse_loss(const Tensor & self, const Tensor & target, int64_t reduction); // aten::mse_loss(Tensor self, Tensor target, int reduction=Mean) -> Tensor
  static std::tuple<Tensor &,Tensor &> nll_loss_forward_out(Tensor & output, Tensor & total_weight, const Tensor & self, const Tensor & target, const Tensor & weight, int64_t reduction, int64_t ignore_index); // aten::nll_loss_forward.output(Tensor self, Tensor target, Tensor? weight, int reduction, int ignore_index, *, Tensor(a!) output, Tensor(b!) total_weight) -> (Tensor(a!), Tensor(b!))
  static std::tuple<Tensor,Tensor> nll_loss_forward(const Tensor & self, const Tensor & target, const Tensor & weight, int64_t reduction, int64_t ignore_index); // aten::nll_loss_forward(Tensor self, Tensor target, Tensor? weight, int reduction, int ignore_index) -> (Tensor output, Tensor total_weight)
  static Tensor & nll_loss_backward_out(Tensor & grad_input, const Tensor & grad_output, const Tensor & self, const Tensor & target, const Tensor & weight, int64_t reduction, int64_t ignore_index, const Tensor & total_weight); // aten::nll_loss_backward.grad_input(Tensor grad_output, Tensor self, Tensor target, Tensor? weight, int reduction, int ignore_index, Tensor total_weight, *, Tensor(a!) grad_input) -> Tensor(a!)
  static Tensor nll_loss_backward(const Tensor & grad_output, const Tensor & self, const Tensor & target, const Tensor & weight, int64_t reduction, int64_t ignore_index, const Tensor & total_weight); // aten::nll_loss_backward(Tensor grad_output, Tensor self, Tensor target, Tensor? weight, int reduction, int ignore_index, Tensor total_weight) -> Tensor
  static Tensor & softplus_out(Tensor & out, const Tensor & self, Scalar beta, Scalar threshold); // aten::softplus.out(Tensor self, Scalar beta=1, Scalar threshold=20, *, Tensor(a!) out) -> Tensor(a!)
  static Tensor softplus(const Tensor & self, Scalar beta, Scalar threshold); // aten::softplus(Tensor self, Scalar beta=1, Scalar threshold=20) -> Tensor
  static Tensor & softplus_backward_out(Tensor & grad_input, const Tensor & grad_output, const Tensor & self, Scalar beta, Scalar threshold, const Tensor & output); // aten::softplus_backward.grad_input(Tensor grad_output, Tensor self, Scalar beta, Scalar threshold, Tensor output, *, Tensor(a!) grad_input) -> Tensor(a!)
  static Tensor softplus_backward(const Tensor & grad_output, const Tensor & self, Scalar beta, Scalar threshold, const Tensor & output); // aten::softplus_backward(Tensor grad_output, Tensor self, Scalar beta, Scalar threshold, Tensor output) -> Tensor
  static Tensor & adaptive_avg_pool2d_out(Tensor & out, const Tensor & self, IntArrayRef output_size); // aten::adaptive_avg_pool2d.out(Tensor self, int[2] output_size, *, Tensor(a!) out) -> Tensor(a!)
  static Tensor _adaptive_avg_pool2d(const Tensor & self, IntArrayRef output_size); // aten::_adaptive_avg_pool2d(Tensor self, int[2] output_size) -> Tensor
  static Tensor adaptive_avg_pool2d(const Tensor & self, IntArrayRef output_size); // aten::adaptive_avg_pool2d(Tensor self, int[2] output_size) -> Tensor
  static Tensor _adaptive_avg_pool2d_backward(const Tensor & grad_output, const Tensor & self); // aten::_adaptive_avg_pool2d_backward(Tensor grad_output, Tensor self) -> Tensor
  static Tensor & avg_pool2d_out(Tensor & out, const Tensor & self, IntArrayRef kernel_size, IntArrayRef stride, IntArrayRef padding, bool ceil_mode, bool count_include_pad, c10::optional<int64_t> divisor_override); // aten::avg_pool2d.out(Tensor self, int[2] kernel_size, int[2] stride=[], int[2] padding=0, bool ceil_mode=False, bool count_include_pad=True, int? divisor_override=None, *, Tensor(a!) out) -> Tensor(a!)
  static Tensor avg_pool2d(const Tensor & self, IntArrayRef kernel_size, IntArrayRef stride, IntArrayRef padding, bool ceil_mode, bool count_include_pad, c10::optional<int64_t> divisor_override); // aten::avg_pool2d(Tensor self, int[2] kernel_size, int[2] stride=[], int[2] padding=0, bool ceil_mode=False, bool count_include_pad=True, int? divisor_override=None) -> Tensor
  static Tensor & avg_pool2d_backward_out(Tensor & grad_input, const Tensor & grad_output, const Tensor & self, IntArrayRef kernel_size, IntArrayRef stride, IntArrayRef padding, bool ceil_mode, bool count_include_pad, c10::optional<int64_t> divisor_override); // aten::avg_pool2d_backward.grad_input(Tensor grad_output, Tensor self, int[2] kernel_size, int[2] stride, int[2] padding, bool ceil_mode, bool count_include_pad, int? divisor_override, *, Tensor(a!) grad_input) -> Tensor(a!)
  static Tensor avg_pool2d_backward(const Tensor & grad_output, const Tensor & self, IntArrayRef kernel_size, IntArrayRef stride, IntArrayRef padding, bool ceil_mode, bool count_include_pad, c10::optional<int64_t> divisor_override); // aten::avg_pool2d_backward(Tensor grad_output, Tensor self, int[2] kernel_size, int[2] stride, int[2] padding, bool ceil_mode, bool count_include_pad, int? divisor_override) -> Tensor
  static std::tuple<Tensor &,Tensor &> max_pool2d_with_indices_out(Tensor & out, Tensor & indices, const Tensor & self, IntArrayRef kernel_size, IntArrayRef stride, IntArrayRef padding, IntArrayRef dilation, bool ceil_mode); // aten::max_pool2d_with_indices.out(Tensor self, int[2] kernel_size, int[2] stride=[], int[2] padding=0, int[2] dilation=1, bool ceil_mode=False, *, Tensor(a!) out, Tensor(b!) indices) -> (Tensor(a!), Tensor(b!))
  static std::tuple<Tensor,Tensor> max_pool2d_with_indices(const Tensor & self, IntArrayRef kernel_size, IntArrayRef stride, IntArrayRef padding, IntArrayRef dilation, bool ceil_mode); // aten::max_pool2d_with_indices(Tensor self, int[2] kernel_size, int[2] stride=[], int[2] padding=0, int[2] dilation=1, bool ceil_mode=False) -> (Tensor, Tensor)
  static Tensor & max_pool2d_with_indices_backward_out(Tensor & grad_input, const Tensor & grad_output, const Tensor & self, IntArrayRef kernel_size, IntArrayRef stride, IntArrayRef padding, IntArrayRef dilation, bool ceil_mode, const Tensor & indices); // aten::max_pool2d_with_indices_backward.grad_input(Tensor grad_output, Tensor self, int[2] kernel_size, int[2] stride, int[2] padding, int[2] dilation, bool ceil_mode, Tensor indices, *, Tensor(a!) grad_input) -> Tensor(a!)
  static Tensor max_pool2d_with_indices_backward(const Tensor & grad_output, const Tensor & self, IntArrayRef kernel_size, IntArrayRef stride, IntArrayRef padding, IntArrayRef dilation, bool ceil_mode, const Tensor & indices); // aten::max_pool2d_with_indices_backward(Tensor grad_output, Tensor self, int[2] kernel_size, int[2] stride, int[2] padding, int[2] dilation, bool ceil_mode, Tensor indices) -> Tensor
  static Tensor & upsample_nearest2d_out(Tensor & out, const Tensor & self, IntArrayRef output_size); // aten::upsample_nearest2d.out(Tensor self, int[2] output_size, *, Tensor(a!) out) -> Tensor(a!)
  static Tensor upsample_nearest2d(const Tensor & self, IntArrayRef output_size); // aten::upsample_nearest2d(Tensor self, int[2] output_size) -> Tensor
  static Tensor & upsample_nearest2d_backward_out(Tensor & grad_input, const Tensor & grad_output, IntArrayRef output_size, IntArrayRef input_size); // aten::upsample_nearest2d_backward.grad_input(Tensor grad_output, int[2] output_size, int[4] input_size, *, Tensor(a!) grad_input) -> Tensor(a!)
  static Tensor upsample_nearest2d_backward(const Tensor & grad_output, IntArrayRef output_size, IntArrayRef input_size); // aten::upsample_nearest2d_backward(Tensor grad_output, int[2] output_size, int[4] input_size) -> Tensor
  static Tensor & sigmoid_backward_out(Tensor & grad_input, const Tensor & grad_output, const Tensor & output); // aten::sigmoid_backward.grad_input(Tensor grad_output, Tensor output, *, Tensor(a!) grad_input) -> Tensor(a!)
  static Tensor sigmoid_backward(const Tensor & grad_output, const Tensor & output); // aten::sigmoid_backward(Tensor grad_output, Tensor output) -> Tensor
  static Tensor & tanh_backward_out(Tensor & grad_input, const Tensor & grad_output, const Tensor & output); // aten::tanh_backward.grad_input(Tensor grad_output, Tensor output, *, Tensor(a!) grad_input) -> Tensor(a!)
  static Tensor tanh_backward(const Tensor & grad_output, const Tensor & output); // aten::tanh_backward(Tensor grad_output, Tensor output) -> Tensor
};

} // namespace at
