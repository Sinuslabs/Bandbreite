/* ------------------------------------------------------------
name: "SoftClipper"
Code generated with Faust 2.69.3 (https://faust.grame.fr)
Compilation options: -lang cpp -rui -nvi -ct 1 -cn _SoftClipper -scn ::faust::dsp -es 1 -mcd 16 -uim -single -ftz 0
------------------------------------------------------------ */

#ifndef  ___SoftClipper_H__
#define  ___SoftClipper_H__

#ifndef FAUSTFLOAT
#define FAUSTFLOAT float
#endif 

#include <algorithm>
#include <cmath>
#include <cstdint>

#ifndef FAUSTCLASS 
#define FAUSTCLASS _SoftClipper
#endif

#ifdef __APPLE__ 
#define exp10f __exp10f
#define exp10 __exp10
#endif

#if defined(_WIN32)
#define RESTRICT __restrict
#else
#define RESTRICT __restrict__
#endif

static float _SoftClipper_faustpower2_f(float value) {
	return value * value;
}

class _SoftClipper final : public ::faust::dsp {
	
 public:
	
	FAUSTFLOAT fHslider0;
	FAUSTFLOAT fHslider1;
	int fSampleRate;
	
 public:
	_SoftClipper() {}

	void metadata(Meta* m) { 
		m->declare("compile_options", "-lang cpp -rui -nvi -ct 1 -cn _SoftClipper -scn ::faust::dsp -es 1 -mcd 16 -uim -single -ftz 0");
		m->declare("filename", "SoftClipper.dsp");
		m->declare("misceffects.lib/cubicnl:author", "Julius O. Smith III");
		m->declare("misceffects.lib/cubicnl:license", "STK-4.3");
		m->declare("misceffects.lib/name", "Misc Effects Library");
		m->declare("misceffects.lib/version", "2.4.0");
		m->declare("name", "SoftClipper");
	}

	static constexpr int getStaticNumInputs() {
		return 2;
	}
	static constexpr int getStaticNumOutputs() {
		return 2;
	}
	int getNumInputs() {
		return 2;
	}
	int getNumOutputs() {
		return 2;
	}
	
	static void classInit(int sample_rate) {
	}
	
	void instanceConstants(int sample_rate) {
		fSampleRate = sample_rate;
	}
	
	void instanceResetUserInterface() {
		fHslider0 = FAUSTFLOAT(0.0f);
		fHslider1 = FAUSTFLOAT(0.6f);
	}
	
	void instanceClear() {
	}
	
	void init(int sample_rate) {
		classInit(sample_rate);
		instanceInit(sample_rate);
	}
	
	void instanceInit(int sample_rate) {
		instanceConstants(sample_rate);
		instanceResetUserInterface();
		instanceClear();
	}
	
	_SoftClipper* clone() {
		return new _SoftClipper();
	}
	
	int getSampleRate() {
		return fSampleRate;
	}
	
	void buildUserInterface(UI* ui_interface) {
		ui_interface->openVerticalBox("SoftClipper");
		ui_interface->declare(&fHslider1, "style", "knob");
		ui_interface->addHorizontalSlider("Drive", &fHslider1, FAUSTFLOAT(0.6f), FAUSTFLOAT(0.0f), FAUSTFLOAT(1.0f), FAUSTFLOAT(0.01f));
		ui_interface->declare(&fHslider0, "style", "knob");
		ui_interface->addHorizontalSlider("Offset", &fHslider0, FAUSTFLOAT(0.0f), FAUSTFLOAT(-1.0f), FAUSTFLOAT(1.0f), FAUSTFLOAT(0.01f));
		ui_interface->closeBox();
	}
	
	void compute(int count, FAUSTFLOAT** RESTRICT inputs, FAUSTFLOAT** RESTRICT outputs) {
		FAUSTFLOAT* input0 = inputs[0];
		FAUSTFLOAT* input1 = inputs[1];
		FAUSTFLOAT* output0 = outputs[0];
		FAUSTFLOAT* output1 = outputs[1];
		float fSlow0 = std::max<float>(-1.0f, std::min<float>(1.0f, float(fHslider0)));
		float fSlow1 = std::pow(1e+01f, 2.0f * std::max<float>(0.0f, std::min<float>(1.0f, float(fHslider1))));
		for (int i0 = 0; i0 < count; i0 = i0 + 1) {
			float fTemp0 = std::max<float>(-1.0f, std::min<float>(1.0f, fSlow0 + fSlow1 * float(input0[i0])));
			output0[i0] = FAUSTFLOAT(fTemp0 * (1.0f - 0.33333334f * _SoftClipper_faustpower2_f(fTemp0)));
			float fTemp1 = std::max<float>(-1.0f, std::min<float>(1.0f, fSlow0 + fSlow1 * float(input1[i0])));
			output1[i0] = FAUSTFLOAT(fTemp1 * (1.0f - 0.33333334f * _SoftClipper_faustpower2_f(fTemp1)));
		}
	}

};

#ifdef FAUST_UIMACROS
	
	#define FAUST_FILE_NAME "SoftClipper.dsp"
	#define FAUST_CLASS_NAME "_SoftClipper"
	#define FAUST_COMPILATION_OPIONS "-lang cpp -rui -nvi -ct 1 -cn _SoftClipper -scn ::faust::dsp -es 1 -mcd 16 -uim -single -ftz 0"
	#define FAUST_INPUTS 2
	#define FAUST_OUTPUTS 2
	#define FAUST_ACTIVES 2
	#define FAUST_PASSIVES 0

	FAUST_ADDHORIZONTALSLIDER("Drive", fHslider1, 0.6f, 0.0f, 1.0f, 0.01f);
	FAUST_ADDHORIZONTALSLIDER("Offset", fHslider0, 0.0f, -1.0f, 1.0f, 0.01f);

	#define FAUST_LIST_ACTIVES(p) \
		p(HORIZONTALSLIDER, Drive, "Drive", fHslider1, 0.6f, 0.0f, 1.0f, 0.01f) \
		p(HORIZONTALSLIDER, Offset, "Offset", fHslider0, 0.0f, -1.0f, 1.0f, 0.01f) \

	#define FAUST_LIST_PASSIVES(p) \

#endif

#endif
