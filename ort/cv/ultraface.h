//
// Created by DefTruth on 2021/3/14.
//

#ifndef LITEHUB_ORT_CV_ULTRAFACE_H
#define LITEHUB_ORT_CV_ULTRAFACE_H

#include "ort/core/ort_core.h"

namespace ortcv
{

  class UltraFace : public BasicOrtHandler
  {

  public:
    explicit UltraFace(const std::string &_onnx_path, unsigned int _num_threads = 1) :
        BasicOrtHandler(_onnx_path, _num_threads)
    {};

    ~UltraFace() override = default; // override

  private:
    static constexpr const float mean_val = 127.0f;
    static constexpr const float scale_val = 1.0 / 128.0f;
    enum NMS
    {
      HARD = 0, BLEND = 1, OFFSET = 2
    };

  private:
    ort::Value transform(const cv::Mat &mat) override;

    void generate_bboxes(std::vector<types::Boxf> &bbox_collection,
                         std::vector<ort::Value> &output_tensors,
                         float score_threshold, float img_height,
                         float img_width); // rescale & exclude
    void nms(std::vector<types::Boxf> &input, std::vector<types::Boxf> &output,
             float iou_threshold, unsigned int topk, unsigned int nms_type);

  public:
    void detect(const cv::Mat &mat, std::vector<types::Boxf> &detected_boxes,
                float score_threshold = 0.7f, float iou_threshold = 0.3f,
                unsigned int topk = 300, unsigned int nms_type = 0);
  };

}

#endif //LITEHUB_ORT_CV_ULTRAFACE_H
