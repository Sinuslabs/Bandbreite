#pragma once

#include "Tube2.h"
#include "Tube2.h"
#include "Tape.h"
#include "IronOxide5.h"
#include "Flutter.h"
#include "Sweeten.h"
#include "ClipSoftly.h"
// These will improve the readability of the connection definition

#define getT(Idx) template get<Idx>()
#define connectT(Idx, target) template connect<Idx>(target)
#define getParameterT(Idx) template getParameter<Idx>()
#define setParameterT(Idx, value) template setParameter<Idx>(value)
#define setParameterWT(Idx, value) template setWrapParameter<Idx>(value)
using namespace scriptnode;
using namespace snex;
using namespace snex::Types;

namespace Band_impl
{
// ==============================| Node & Parameter type declarations |==============================

template <int NV>
using minmax1_t = control::minmax<NV, 
                                  parameter::plain<core::gain<NV>, 0>>;

template <int NV>
using tubeinputminmax_mod = parameter::chain<ranges::Identity, 
                                             parameter::plain<project::Tube2<NV>, 0>, 
                                             parameter::plain<project::Tube2<NV>, 0>>;

template <int NV>
using tubeinputminmax_t = control::minmax<NV, 
                                          tubeinputminmax_mod<NV>>;

template <int NV>
using split_t = container::split<parameter::empty, 
                                 wrap::fix<1, tubeinputminmax_t<NV>>>;

template <int NV>
using modchain_t_ = container::chain<parameter::empty, 
                                     wrap::fix<1, split_t<NV>>>;

template <int NV>
using modchain_t = wrap::control_rate<modchain_t_<NV>>;

template <int NV>
using Saturation_t = container::chain<parameter::empty, 
                                      wrap::fix<2, modchain_t<NV>>, 
                                      project::Tube2<NV>, 
                                      project::Tube2<NV>>;

DECLARE_PARAMETER_RANGE_SKEW(dry_wet_mixer2_c0Range, 
                             -100., 
                             0., 
                             5.42227);

template <int NV>
using dry_wet_mixer2_c0 = parameter::from0To1<core::gain<NV>, 
                                              0, 
                                              dry_wet_mixer2_c0Range>;

template <int NV> using dry_wet_mixer2_c1 = dry_wet_mixer2_c0<NV>;

template <int NV>
using dry_wet_mixer2_multimod = parameter::list<dry_wet_mixer2_c0<NV>, dry_wet_mixer2_c1<NV>>;

template <int NV>
using dry_wet_mixer2_t = control::xfader<dry_wet_mixer2_multimod<NV>, 
                                         faders::cosine_half>;

template <int NV>
using dry_path2_t = container::chain<parameter::empty, 
                                     wrap::fix<2, dry_wet_mixer2_t<NV>>, 
                                     core::gain<NV>>;

template <int NV>
using low_invert_t = control::pma<NV, 
                                  parameter::plain<project::IronOxide5<NV>, 2>>;

template <int NV>
using modchain1_t_ = container::chain<parameter::empty, 
                                      wrap::fix<1, low_invert_t<NV>>, 
                                      control::minmax<NV, parameter::empty>>;

template <int NV>
using modchain1_t = wrap::control_rate<modchain1_t_<NV>>;

template <int NV>
using wet_path2_t = container::chain<parameter::empty, 
                                     wrap::fix<2, modchain1_t<NV>>, 
                                     project::Tape<NV>, 
                                     core::gain<NV>, 
                                     project::IronOxide5<NV>, 
                                     project::Flutter<NV>, 
                                     core::gain<NV>>;

namespace TapeDryWet_t_parameters
{
}

template <int NV>
using TapeDryWet_t = container::split<parameter::plain<Band_impl::dry_wet_mixer2_t<NV>, 0>, 
                                      wrap::fix<2, dry_path2_t<NV>>, 
                                      wet_path2_t<NV>>;

namespace Band_t_parameters
{
// Parameter list for Band_impl::Band_t ------------------------------------------------------------

template <int NV>
using Tube = parameter::chain<ranges::Identity, 
                              parameter::plain<project::Tube2<NV>, 1>, 
                              parameter::plain<project::Tube2<NV>, 1>, 
                              parameter::plain<Band_impl::tubeinputminmax_t<NV>, 0>>;

template <int NV>
using Flutter = parameter::chain<ranges::Identity, 
                                 parameter::plain<project::IronOxide5<NV>, 3>, 
                                 parameter::plain<project::Flutter<NV>, 0>>;

template <int NV>
using Tape = parameter::plain<Band_impl::TapeDryWet_t<NV>, 
                              0>;
template <int NV>
using Tape_Slam = parameter::plain<project::Tape<NV>, 0>;
template <int NV>
using Tape_high = parameter::plain<project::IronOxide5<NV>, 
                                   1>;
template <int NV>
using Tape_low = parameter::plain<Band_impl::low_invert_t<NV>, 
                                  0>;
template <int NV>
using Tape_noise = parameter::plain<project::IronOxide5<NV>, 
                                    4>;
template <int NV>
using Tape_Sweeten = parameter::plain<project::Sweeten<NV>, 0>;
template <int NV>
using Hot = parameter::plain<Band_impl::minmax1_t<NV>, 
                             0>;
template <int NV>
using Band_t_plist = parameter::list<Tube<NV>, 
                                     Tape<NV>, 
                                     Tape_Slam<NV>, 
                                     Tape_high<NV>, 
                                     Tape_low<NV>, 
                                     Flutter<NV>, 
                                     Tape_noise<NV>, 
                                     Tape_Sweeten<NV>, 
                                     Hot<NV>>;
}

template <int NV>
using Band_t_ = container::chain<Band_t_parameters::Band_t_plist<NV>, 
                                 wrap::fix<2, minmax1_t<NV>>, 
                                 core::gain<NV>, 
                                 Saturation_t<NV>, 
                                 TapeDryWet_t<NV>, 
                                 project::Sweeten<NV>, 
                                 project::ClipSoftly<NV>>;

// =================================| Root node initialiser class |=================================

template <int NV> struct instance: public Band_impl::Band_t_<NV>
{
	
	struct metadata
	{
		static const int NumTables = 0;
		static const int NumSliderPacks = 0;
		static const int NumAudioFiles = 0;
		static const int NumFilters = 0;
		static const int NumDisplayBuffers = 0;
		
		SNEX_METADATA_ID(Band);
		SNEX_METADATA_NUM_CHANNELS(2);
		SNEX_METADATA_ENCODED_PARAMETERS(152)
		{
			0x005B, 0x0000, 0x5400, 0x6275, 0x0065, 0x0000, 0x0000, 0x0000, 
            0x3F80, 0x0000, 0x0000, 0x0000, 0x3F80, 0x0000, 0x0000, 0x015B, 
            0x0000, 0x5400, 0x7061, 0x0065, 0x0000, 0x0000, 0x0000, 0x3F80, 
            0x0000, 0x0000, 0x0000, 0x3F80, 0x0000, 0x0000, 0x025B, 0x0000, 
            0x5400, 0x7061, 0x5F65, 0x6C53, 0x6D61, 0x0000, 0x0000, 0x0000, 
            0x8000, 0x443F, 0x868F, 0x003E, 0x8000, 0x003F, 0x0000, 0x5B00, 
            0x0003, 0x0000, 0x6154, 0x6570, 0x685F, 0x6769, 0x0068, 0x0000, 
            0x0000, 0x0000, 0x3F80, 0x51CB, 0x3F00, 0x0000, 0x3F80, 0x0000, 
            0x0000, 0x045B, 0x0000, 0x5400, 0x7061, 0x5F65, 0x6F6C, 0x0077, 
            0x0000, 0x0000, 0x0000, 0x3F80, 0x9106, 0x3F00, 0x0000, 0x3F80, 
            0x0000, 0x0000, 0x055B, 0x0000, 0x4600, 0x756C, 0x7474, 0x7265, 
            0x0000, 0x0000, 0x0000, 0x8000, 0x003F, 0x0000, 0x0000, 0x8000, 
            0x003F, 0x0000, 0x5B00, 0x0006, 0x0000, 0x6154, 0x6570, 0x6E5F, 
            0x696F, 0x6573, 0x0000, 0x0000, 0x0000, 0x8000, 0x003F, 0x0000, 
            0x0000, 0x8000, 0x003F, 0x0000, 0x5B00, 0x0007, 0x0000, 0x6154, 
            0x6570, 0x535F, 0x6577, 0x7465, 0x6E65, 0x0000, 0x0000, 0x0000, 
            0x8000, 0x003F, 0x0000, 0x0000, 0x8000, 0x003F, 0x0000, 0x5B00, 
            0x0008, 0x0000, 0x6F48, 0x0074, 0x0000, 0x0000, 0x0000, 0x3F80, 
            0x0000, 0x3F80, 0x0000, 0x3F80, 0x0000, 0x3F80, 0x0000, 0x0000
		};
	};
	
	instance()
	{
		// Node References -------------------------------------------------------------------------
		
		auto& minmax1 = this->getT(0);                                 // Band_impl::minmax1_t<NV>
		auto& gain = this->getT(1);                                    // core::gain<NV>
		auto& Saturation = this->getT(2);                              // Band_impl::Saturation_t<NV>
		auto& modchain = this->getT(2).getT(0);                        // Band_impl::modchain_t<NV>
		auto& split = this->getT(2).getT(0).getT(0);                   // Band_impl::split_t<NV>
		auto& tubeinputminmax = this->getT(2).getT(0).getT(0).getT(0); // Band_impl::tubeinputminmax_t<NV>
		auto& Tube2 = this->getT(2).getT(1);                           // project::Tube2<NV>
		auto& Tube3 = this->getT(2).getT(2);                           // project::Tube2<NV>
		auto& TapeDryWet = this->getT(3);                              // Band_impl::TapeDryWet_t<NV>
		auto& dry_path2 = this->getT(3).getT(0);                       // Band_impl::dry_path2_t<NV>
		auto& dry_wet_mixer2 = this->getT(3).getT(0).getT(0);          // Band_impl::dry_wet_mixer2_t<NV>
		auto& dry_gain2 = this->getT(3).getT(0).getT(1);               // core::gain<NV>
		auto& wet_path2 = this->getT(3).getT(1);                       // Band_impl::wet_path2_t<NV>
		auto& modchain1 = this->getT(3).getT(1).getT(0);               // Band_impl::modchain1_t<NV>
		auto& low_invert = this->getT(3).getT(1).getT(0).getT(0);      // Band_impl::low_invert_t<NV>
		auto& minmax = this->getT(3).getT(1).getT(0).getT(1);          // control::minmax<NV, parameter::empty>
		auto& Tape2 = this->getT(3).getT(1).getT(1);                   // project::Tape<NV>
		auto& SlamGainMatcher = this->getT(3).getT(1).getT(2);         // core::gain<NV>
		auto& IronOxide5 = this->getT(3).getT(1).getT(3);              // project::IronOxide5<NV>
		auto& Flutter = this->getT(3).getT(1).getT(4);                 // project::Flutter<NV>
		auto& wet_gain2 = this->getT(3).getT(1).getT(5);               // core::gain<NV>
		auto& Sweeten = this->getT(4);                                 // project::Sweeten<NV>
		auto& ClipSoftly = this->getT(5);                              // project::ClipSoftly<NV>
		
		// Parameter Connections -------------------------------------------------------------------
		
		TapeDryWet.getParameterT(0).connectT(0, dry_wet_mixer2); // DryWet -> dry_wet_mixer2::Value
		auto& Tube_p = this->getParameterT(0);
		Tube_p.connectT(0, Tube2);           // Tube -> Tube2::Tube
		Tube_p.connectT(1, Tube3);           // Tube -> Tube3::Tube
		Tube_p.connectT(2, tubeinputminmax); // Tube -> tubeinputminmax::Value
		
		this->getParameterT(1).connectT(0, TapeDryWet); // Tape -> TapeDryWet::DryWet
		
		this->getParameterT(2).connectT(0, Tape2); // Tape_Slam -> Tape2::Slam
		
		this->getParameterT(3).connectT(0, IronOxide5); // Tape_high -> IronOxide5::TapeHigh
		
		this->getParameterT(4).connectT(0, low_invert); // Tape_low -> low_invert::Value
		
		auto& Flutter_p = this->getParameterT(5);
		Flutter_p.connectT(0, IronOxide5); // Flutter -> IronOxide5::Flutter
		Flutter_p.connectT(1, Flutter);    // Flutter -> Flutter::Flutter
		
		this->getParameterT(6).connectT(0, IronOxide5); // Tape_noise -> IronOxide5::Noise
		
		this->getParameterT(7).connectT(0, Sweeten); // Tape_Sweeten -> Sweeten::Sweeten
		
		this->getParameterT(8).connectT(0, minmax1); // Hot -> minmax1::Value
		
		// Modulation Connections ------------------------------------------------------------------
		
		minmax1.getWrappedObject().getParameter().connectT(0, gain);          // minmax1 -> gain::Gain
		tubeinputminmax.getWrappedObject().getParameter().connectT(0, Tube2); // tubeinputminmax -> Tube2::Input
		tubeinputminmax.getWrappedObject().getParameter().connectT(1, Tube3); // tubeinputminmax -> Tube3::Input
		auto& dry_wet_mixer2_p = dry_wet_mixer2.getWrappedObject().getParameter();
		dry_wet_mixer2_p.getParameterT(0).connectT(0, dry_gain2);             // dry_wet_mixer2 -> dry_gain2::Gain
		dry_wet_mixer2_p.getParameterT(1).connectT(0, wet_gain2);             // dry_wet_mixer2 -> wet_gain2::Gain
		low_invert.getWrappedObject().getParameter().connectT(0, IronOxide5); // low_invert -> IronOxide5::TapeLow
		
		// Default Values --------------------------------------------------------------------------
		
		;                             // minmax1::Value is automated
		minmax1.setParameterT(1, 0.); // control::minmax::Minimum
		minmax1.setParameterT(2, 3.); // control::minmax::Maximum
		minmax1.setParameterT(3, 1.); // control::minmax::Skew
		minmax1.setParameterT(4, 0.); // control::minmax::Step
		minmax1.setParameterT(5, 0.); // control::minmax::Polarity
		
		;                           // gain::Gain is automated
		gain.setParameterT(1, 20.); // core::gain::Smoothing
		gain.setParameterT(2, 0.);  // core::gain::ResetValue
		
		;                                           // tubeinputminmax::Value is automated
		tubeinputminmax.setParameterT(1, 0.497614); // control::minmax::Minimum
		tubeinputminmax.setParameterT(2, 0.807704); // control::minmax::Maximum
		tubeinputminmax.setParameterT(3, 0.115888); // control::minmax::Skew
		tubeinputminmax.setParameterT(4, 0.);       // control::minmax::Step
		tubeinputminmax.setParameterT(5, 0.);       // control::minmax::Polarity
		
		; // Tube2::Input is automated
		; // Tube2::Tube is automated
		
		; // Tube3::Input is automated
		; // Tube3::Tube is automated
		
		; // TapeDryWet::DryWet is automated
		
		; // dry_wet_mixer2::Value is automated
		
		;                                // dry_gain2::Gain is automated
		dry_gain2.setParameterT(1, 20.); // core::gain::Smoothing
		dry_gain2.setParameterT(2, 0.);  // core::gain::ResetValue
		
		;                                 // low_invert::Value is automated
		low_invert.setParameterT(1, -1.); // control::pma::Multiply
		low_invert.setParameterT(2, 1.);  // control::pma::Add
		
		minmax.setParameterT(0, 0.); // control::minmax::Value
		minmax.setParameterT(1, 0.); // control::minmax::Minimum
		minmax.setParameterT(2, 1.); // control::minmax::Maximum
		minmax.setParameterT(3, 1.); // control::minmax::Skew
		minmax.setParameterT(4, 0.); // control::minmax::Step
		minmax.setParameterT(5, 0.); // control::minmax::Polarity
		
		;                            // Tape2::Slam is automated
		Tape2.setParameterT(1, 0.5); // project::Tape::Bump
		
		SlamGainMatcher.setParameterT(0, 0.);  // core::gain::Gain
		SlamGainMatcher.setParameterT(1, 0.9); // core::gain::Smoothing
		SlamGainMatcher.setParameterT(2, 0.);  // core::gain::ResetValue
		
		IronOxide5.setParameterT(0, 0.5); // project::IronOxide5::InputTrim
		;                                 // IronOxide5::TapeHigh is automated
		;                                 // IronOxide5::TapeLow is automated
		;                                 // IronOxide5::Flutter is automated
		;                                 // IronOxide5::Noise is automated
		IronOxide5.setParameterT(5, 0.5); // project::IronOxide5::OutputTrim
		IronOxide5.setParameterT(6, 1.);  // project::IronOxide5::InvDryWet
		
		; // Flutter::Flutter is automated
		
		;                                // wet_gain2::Gain is automated
		wet_gain2.setParameterT(1, 20.); // core::gain::Smoothing
		wet_gain2.setParameterT(2, 0.);  // core::gain::ResetValue
		
		; // Sweeten::Sweeten is automated
		
		this->setParameterT(0, 0.);
		this->setParameterT(1, 0.);
		this->setParameterT(2, 0.262812);
		this->setParameterT(3, 0.501248);
		this->setParameterT(4, 0.502213);
		this->setParameterT(5, 0.);
		this->setParameterT(6, 0.);
		this->setParameterT(7, 0.);
		this->setParameterT(8, 1.);
	}
	
	static constexpr bool isPolyphonic() { return NV > 1; };
	
	static constexpr bool hasTail() { return true; };
	
	static constexpr bool isSuspendedOnSilence() { return false; };
};
}

#undef getT
#undef connectT
#undef setParameterT
#undef setParameterWT
#undef getParameterT
// ======================================| Public Definition |======================================

namespace project
{
// polyphonic template declaration

template <int NV>
using Band = wrap::node<Band_impl::instance<NV>>;
}


