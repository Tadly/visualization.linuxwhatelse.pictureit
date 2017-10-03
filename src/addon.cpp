#define GL_GLEXT_PROTOTYPES
#include <kodi/addon-instance/Visualization.h>

#include <GL/gl.h>

#include <PictureIt/pictureit.hpp>


class CVisPictureIt : public kodi::addon::CAddonBase,
                      public kodi::addon::CInstanceVisualization {
public:
    CVisPictureIt();
    virtual ~CVisPictureIt();

    virtual ADDON_STATUS Create() override;
    virtual bool GetPresets(std::vector<std::string>&) override;
    virtual bool Start(int channels, int samplesPerSec, int bitsPerSample,
                       std::string songName) override;
    virtual void Stop() override;
    virtual void Render() override;
    virtual void AudioData(const float*, int, float*, int) override;
    virtual bool UpdateTrack(const VisTrack &track) override;

private:
    PictureIt *pi = nullptr;
    Buffer<float> *buffer = nullptr;
    FFT *fft = nullptr;
};

CVisPictureIt::CVisPictureIt() {}

CVisPictureIt::~CVisPictureIt() {}

ADDON_STATUS CVisPictureIt::Create() {
    fprintf(stdout, "GL Version: %s\n", glGetString(GL_VERSION));
    fprintf(stdout, "GLSL Version: %s\n", glGetString(GL_SHADING_LANGUAGE_VERSION));

    // Create PictureIt and set some initial properties
    PI::Config::Transition pi_trans;
    pi_trans.speed = 50;

    PI::Config::PictureIt pi_cfg = PI::Config::PictureIt();
    pi_cfg.max_fps = 120;
    pi_cfg.update_interval = 15;
    pi_cfg.pick_random = true;
    pi_cfg.recursive = true;
    pi_cfg.display_mode = PI::Config::Texture::Mode::STRETCH;
    pi_cfg.transition = pi_trans;
    pi_cfg.image_dir = "/home/tadly/Pictures/test";

    try {
        this->pi = new PictureIt(pi_cfg);

        PI::Config::FFT fft_cfg = PI::Config::FFT();
        fft_cfg.window = PI::Config::FFT::Window::EXACT_BLACKMAN;
        this->fft = new FFT(fft_cfg);
    } catch(std::runtime_error& err) {
        fprintf(stderr, "%s\n", err.what());
        return ADDON_STATUS_UNKNOWN;
    }

    return ADDON_STATUS_OK;
}


bool CVisPictureIt::GetPresets(std::vector<std::string>& presets) {
    return false;
}

bool CVisPictureIt::Start(int iChannels, int iSamplesPerSec,
                          int iBitsPerSample, std::string szSongName) {
    return true;
}

void CVisPictureIt::Stop() {}
bool CVisPictureIt::UpdateTrack(const VisTrack &track) {
    return true;
}

void CVisPictureIt::Render() {
    if (this->pi == nullptr)
        return;

    //this->fft->calculate(*this->buffer);
    this->pi->draw(*fft);
}

void CVisPictureIt::AudioData(const float* pAudioData, int iAudioDataLength,
                              float *pFreqData, int iFreqDataLength) {
    //this->buffer->write(*pAudioData, iAudioDataLength);
}


ADDONCREATOR(CVisPictureIt)
