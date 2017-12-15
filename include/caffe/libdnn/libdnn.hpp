#ifndef CAFFE_LIBDNN_LIBDNN_HPP_
#define CAFFE_LIBDNN_LIBDNN_HPP_

#include <iomanip>
#include <map>
#include <memory>
#include <string>
#include <vector>
#include "caffe/common.hpp"
#include "caffe/backend/device.hpp"
#include "caffe/libdnn/libdnn_tuner.hpp"

namespace caffe {

enum LibDNNAccumulatePrecision {
  LIBDNN_ACCUMULATE_PREC_NATIVE = 0,
  LIBDNN_ACCUMULATE_PREC_8 = 1,
  LIBDNN_ACCUMULATE_PREC_16 = 2,
  LIBDNN_ACCUMULATE_PREC_32 = 3,
  LIBDNN_ACCUMULATE_PREC_64 = 4
};

class LibDNNBase {

};

template<typename Dtype, typename MItype, typename MOtype>
class LibDNN : public LibDNNBase {
 protected:
  explicit LibDNN(Device* dev_ptr);
  virtual void GenerateKernels() = 0;
  virtual bool CompileKernels() = 0;
  virtual string string_identifier() = 0;
  string generate_gemm_core(shared_ptr<LibDNNTuner> tuner, bool dterm,
                            LibDNNAccumulatePrecision prec);
  string generate_accreg_init(shared_ptr<LibDNNTuner> tuner, bool dterm,
                              bool load, bool beta_term,
                              LibDNNAccumulatePrecision prec);

  Device* dev_ptr_;
  shared_ptr<DeviceProgram> program_;
  bool fast_unsafe_math_;
};

}  // namespace caffe

#endif /* CAFFE_GREENTEA_LIBDNN_HPP_ */
