#pragma once

#include "lge_device.hpp"

#include <string>
#include <vector>

namespace lge2 {

struct PipelineConfigInfo {
  PipelineConfigInfo()                                     = default;
  PipelineConfigInfo(const PipelineConfigInfo&)            = delete;
  PipelineConfigInfo& operator=(const PipelineConfigInfo&) = delete;

  VkPipelineViewportStateCreateInfo viewportInfo;
  VkPipelineInputAssemblyStateCreateInfo inputAssemblyInfo;
  VkPipelineRasterizationStateCreateInfo rasterizationInfo;
  VkPipelineMultisampleStateCreateInfo multisampleInfo;
  VkPipelineColorBlendAttachmentState colorBlendAttachment;
  VkPipelineColorBlendStateCreateInfo colorBlendInfo;
  VkPipelineDepthStencilStateCreateInfo depthStencilInfo;
  std::vector<VkDynamicState> dynamicStateEnables;
  VkPipelineDynamicStateCreateInfo dynamicStateInfo;
  VkPipelineLayout pipelineLayout = nullptr;
  VkRenderPass renderPass         = nullptr;
  uint32_t subpass                = 0;
};

class LgePipeline {
public:
  LgePipeline(
      LgeDevice& device, const std::string& vertex_shader_path,
      const std::string& fragment_shader_path, const PipelineConfigInfo& configInfo);

  ~LgePipeline();

  LgePipeline(const LgePipeline&)            = delete;
  LgePipeline& operator=(const LgePipeline&) = delete;

  void bind(VkCommandBuffer commandBuffer);

  static void defaultPipelineConfigInfo(PipelineConfigInfo& configInfo);

private:
  static std::vector<char> readFile(const std::string& path);

  void createGraphicsPipeline(
      const std::string& vertex_shader_path, const std::string& fragment_shader_path,
      const PipelineConfigInfo& configInfo);

  void createShaderModule(const std::vector<char>& code, VkShaderModule* shaderModule);

  LgeDevice& lgeDevice;
  VkPipeline graphicsPipeline;
  VkShaderModule vertShaderModule;
  VkShaderModule fragShaderModule;
};

} // namespace lge
