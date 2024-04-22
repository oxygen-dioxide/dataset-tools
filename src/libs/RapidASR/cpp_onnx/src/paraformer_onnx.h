#pragma once
#ifndef PARAFORMER_MODELIMP_H
#    define PARAFORMER_MODELIMP_H

#    include "FeatureExtract.h"

#    include <Model.h>
#    include <onnxruntime_cxx_api.h>

#    include "Vocab.h"

namespace paraformer {

    class ModelImp : public Model {
    private:
        FeatureExtract *fe;

        Vocab *vocab;

        static void apply_lfr(Tensor<float> *&din);
        static void apply_cmvn(const Tensor<float> *din);

        string greedy_search(float *in, const int &nLen) const;

#    ifdef _WIN_X86
        Ort::MemoryInfo m_memoryInfo = Ort::MemoryInfo::CreateCpu(OrtDeviceAllocator, OrtMemTypeCPU);
#    else
        Ort::MemoryInfo m_memoryInfo = Ort::MemoryInfo::CreateCpu(OrtArenaAllocator, OrtMemTypeDefault);
#    endif

        Ort::Session *m_session = nullptr;
        Ort::Env env = Ort::Env(ORT_LOGGING_LEVEL_ERROR, "paraformer");
        Ort::SessionOptions sessionOptions = Ort::SessionOptions();

        vector<string> m_strInputNames, m_strOutputNames;
        vector<const char *> m_szInputNames;
        vector<const char *> m_szOutputNames;

    public:
        explicit ModelImp(const char *path, const int &nNumThread = 0);
        ~ModelImp() override;
        void reset() override;
        string forward(float *din, int len, int flag) override;
    };

} // namespace paraformer
#endif
