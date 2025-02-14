//
// Created by DefTruth on 2021/4/9.
//

#ifndef LITEHUB_ORT_CV_COLORIZER_H
#define LITEHUB_ORT_CV_COLORIZER_H

#include "ort/core/ort_core.h"

namespace ortcv
{
  class Colorizer : public BasicOrtHandler
  {
  public:
    explicit Colorizer(const std::string &_onnx_path, unsigned int _num_threads = 1) :
        BasicOrtHandler(_onnx_path, _num_threads)
    {};

    ~Colorizer() override = default;

  private:
    ort::Value transform(const cv::Mat &mat) override;

  public:
    void detect(const cv::Mat &mat, types::ColorizeContent &colorize_content);
  };
}

#endif //LITEHUB_ORT_CV_COLORIZER_H
