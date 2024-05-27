#pragma once

#include "Tube2.h"
#include "Tube2.h"
#include "Tape.h"
#include "IronOxide5.h"
#include "Flutter.h"
#include "Sweeten.h"
#include "GrooveWear.h"
#include "TapeDust.h"
#include "Pockey2.h"
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
using low_invert_t = control::pma<NV, 
                                  parameter::plain<project::IronOxide5<NV>, 2>>;

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
using wet_path2_t = container::chain<parameter::empty, 
                                     wrap::fix<2, project::Tape<NV>>, 
                                     project::IronOxide5<NV>, 
                                     project::Flutter<NV>, 
                                     project::Sweeten<NV>, 
                                     core::gain<NV>>;

namespace dry_wet3_t_parameters
{
}

template <int NV>
using dry_wet3_t = container::split<parameter::plain<Band_impl::dry_wet_mixer2_t<NV>, 0>, 
                                    wrap::fix<2, dry_path2_t<NV>>, 
                                    wet_path2_t<NV>>;

template <int NV> using dry_wet_mixer1_c0 = dry_wet_mixer2_c0<NV>;

template <int NV> using dry_wet_mixer1_c1 = dry_wet_mixer2_c0<NV>;

template <int NV>
using dry_wet_mixer1_multimod = parameter::list<dry_wet_mixer1_c0<NV>, dry_wet_mixer1_c1<NV>>;

template <int NV>
using dry_wet_mixer1_t = control::xfader<dry_wet_mixer1_multimod<NV>, 
                                         faders::cosine_half>;

template <int NV>
using dry_path1_t = container::chain<parameter::empty, 
                                     wrap::fix<2, dry_wet_mixer1_t<NV>>, 
                                     core::gain<NV>>;

template <int NV>
using chain_t = container::chain<parameter::empty, 
                                 wrap::fix<2, project::GrooveWear<NV>>, 
                                 project::TapeDust<NV>>;
template <int NV>
using branch1_t = container::branch<parameter::empty, 
                                    wrap::fix<2, chain_t<NV>>, 
                                    project::Pockey2<NV>>;

template <int NV>
using wet_path1_t = container::chain<parameter::empty, 
                                     wrap::fix<2, branch1_t<NV>>, 
                                     core::gain<NV>>;

namespace dry_wet2_t_parameters
{
}

template <int NV>
using dry_wet2_t = container::split<parameter::plain<Band_impl::dry_wet_mixer1_t<NV>, 0>, 
                                    wrap::fix<2, dry_path1_t<NV>>, 
                                    wet_path1_t<NV>>;

namespace Band_t_parameters
{
// Parameter list for Band_impl::Band_t ------------------------------------------------------------

template <int NV>
using Tube = parameter::chain<ranges::Identity, 
                              parameter::plain<project::Tube2<NV>, 1>, 
                              parameter::plain<project::Tube2<NV>, 1>>;

template <int NV>
using Flutter = parameter::chain<ranges::Identity, 
                                 parameter::plain<project::IronOxide5<NV>, 3>, 
                                 parameter::plain<project::Flutter<NV>, 0>>;

template <int NV>
using Tape = parameter::plain<Band_impl::dry_wet3_t<NV>, 
                              0>;
template <int NV>
using Tape_Slam = parameter::plain<project::Tape<NV>, 0>;
template <int NV>
using Tape_Bump = parameter::plain<project::Tape<NV>, 1>;
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
using Textures_Mode = parameter::plain<Band_impl::branch1_t<NV>, 
                                       0>;
template <int NV>
using Textures_Wear = parameter::plain<project::GrooveWear<NV>, 
                                       0>;
template <int NV>
using Textures_Dust = parameter::plain<project::TapeDust<NV>, 0>;
template <int NV>
using Textures_Freq = parameter::plain<project::Pockey2<NV>, 0>;
template <int NV>
using Textures_Rez = parameter::plain<project::Pockey2<NV>, 1>;
template <int NV>
using Textures = parameter::plain<Band_impl::dry_wet2_t<NV>, 
                                  0>;
template <int NV>
using Band_t_plist = parameter::list<Tube<NV>, 
                                     Tape<NV>, 
                                     Tape_Slam<NV>, 
                                     Tape_Bump<NV>, 
                                     Tape_high<NV>, 
                                     Tape_low<NV>, 
                                     Flutter<NV>, 
                                     Tape_noise<NV>, 
                                     Tape_Sweeten<NV>, 
                                     Textures_Mode<NV>, 
                                     Textures_Wear<NV>, 
                                     Textures_Dust<NV>, 
                                     Textures_Freq<NV>, 
                                     Textures_Rez<NV>, 
                                     Textures<NV>>;
}

template <int NV>
using Band_t_ = container::chain<Band_t_parameters::Band_t_plist<NV>, 
                                 wrap::fix<2, low_invert_t<NV>>, 
                                 project::Tube2<NV>, 
                                 project::Tube2<NV>, 
                                 dry_wet3_t<NV>, 
                                 dry_wet2_t<NV>, 
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
		SNEX_METADATA_ENCODED_PARAMETERS(268)
		{
			0x005B, 0x0000, 0x5400, 0x6275, 0x0065, 0x0000, 0x0000, 0x0000, 
            0x3F80, 0x0000, 0x0000, 0x0000, 0x3F80, 0x0000, 0x0000, 0x015B, 
            0x0000, 0x5400, 0x7061, 0x0065, 0x0000, 0x0000, 0x0000, 0x3F80, 
            0x0000, 0x3F80, 0x0000, 0x3F80, 0x0000, 0x0000, 0x025B, 0x0000, 
            0x5400, 0x7061, 0x5F65, 0x6C53, 0x6D61, 0x0000, 0x0000, 0x0000, 
            0x8000, 0x003F, 0x0000, 0x0000, 0x8000, 0x003F, 0x0000, 0x5B00, 
            0x0003, 0x0000, 0x6154, 0x6570, 0x425F, 0x6D75, 0x0070, 0x0000, 
            0x0000, 0x0000, 0x3F80, 0x0BD7, 0x3F1E, 0x0000, 0x3F80, 0x0000, 
            0x0000, 0x045B, 0x0000, 0x5400, 0x7061, 0x5F65, 0x6968, 0x6867, 
            0x0000, 0x0000, 0x0000, 0x8000, 0x003F, 0x8000, 0x003F, 0x8000, 
            0x003F, 0x0000, 0x5B00, 0x0005, 0x0000, 0x6154, 0x6570, 0x6C5F, 
            0x776F, 0x0000, 0x0000, 0x0000, 0x8000, 0x613F, 0x0F26, 0x003F, 
            0x8000, 0x003F, 0x0000, 0x5B00, 0x0006, 0x0000, 0x6C46, 0x7475, 
            0x6574, 0x0072, 0x0000, 0x0000, 0x0000, 0x3F80, 0x0000, 0x0000, 
            0x0000, 0x3F80, 0x0000, 0x0000, 0x075B, 0x0000, 0x5400, 0x7061, 
            0x5F65, 0x6F6E, 0x7369, 0x0065, 0x0000, 0x0000, 0x0000, 0x3F80, 
            0x0000, 0x0000, 0x0000, 0x3F80, 0x0000, 0x0000, 0x085B, 0x0000, 
            0x5400, 0x7061, 0x5F65, 0x7753, 0x6565, 0x6574, 0x006E, 0x0000, 
            0x0000, 0x0000, 0x3F80, 0xDD2F, 0x3994, 0x0000, 0x3F80, 0x0000, 
            0x0000, 0x095B, 0x0000, 0x5400, 0x7865, 0x7574, 0x6572, 0x5F73, 
            0x6F4D, 0x6564, 0x0000, 0x0000, 0x0000, 0x8000, 0x003F, 0x8000, 
            0x003F, 0x8000, 0x003F, 0x8000, 0x5B3F, 0x000A, 0x0000, 0x6554, 
            0x7478, 0x7275, 0x7365, 0x575F, 0x6165, 0x0072, 0x0000, 0x0000, 
            0x0000, 0x3F80, 0xF360, 0x3F00, 0x0000, 0x3F80, 0x0000, 0x0000, 
            0x0B5B, 0x0000, 0x5400, 0x7865, 0x7574, 0x6572, 0x5F73, 0x7544, 
            0x7473, 0x0000, 0x0000, 0x0000, 0x8000, 0x003F, 0x0000, 0x0000, 
            0x8000, 0x003F, 0x0000, 0x5B00, 0x000C, 0x0000, 0x6554, 0x7478, 
            0x7275, 0x7365, 0x465F, 0x6572, 0x0071, 0x0000, 0x0000, 0x0000, 
            0x3F80, 0x0000, 0x3F80, 0x0000, 0x3F80, 0x0000, 0x0000, 0x0D5B, 
            0x0000, 0x5400, 0x7865, 0x7574, 0x6572, 0x5F73, 0x6552, 0x007A, 
            0x0000, 0x0000, 0x0000, 0x3F80, 0x052F, 0x3F39, 0x0000, 0x3F80, 
            0x0000, 0x0000, 0x0E5B, 0x0000, 0x5400, 0x7865, 0x7574, 0x6572, 
            0x0073, 0x0000, 0x0000, 0x0000, 0x3F80, 0x0000, 0x3F80, 0x0000, 
            0x3F80, 0x0000, 0x0000, 0x0000
		};
	};
	
	instance()
	{
		// Node References -------------------------------------------------------------------------
		
		auto& low_invert = this->getT(0);                                 // Band_impl::low_invert_t<NV>
		auto& Tube2 = this->getT(1);                                      // project::Tube2<NV>
		auto& Tube3 = this->getT(2);                                      // project::Tube2<NV>
		auto& dry_wet3 = this->getT(3);                                   // Band_impl::dry_wet3_t<NV>
		auto& dry_path2 = this->getT(3).getT(0);                          // Band_impl::dry_path2_t<NV>
		auto& dry_wet_mixer2 = this->getT(3).getT(0).getT(0);             // Band_impl::dry_wet_mixer2_t<NV>
		auto& dry_gain2 = this->getT(3).getT(0).getT(1);                  // core::gain<NV>
		auto& wet_path2 = this->getT(3).getT(1);                          // Band_impl::wet_path2_t<NV>
		auto& Tape = this->getT(3).getT(1).getT(0);                       // project::Tape<NV>
		auto& IronOxide5 = this->getT(3).getT(1).getT(1);                 // project::IronOxide5<NV>
		auto& Flutter = this->getT(3).getT(1).getT(2);                    // project::Flutter<NV>
		auto& Sweeten = this->getT(3).getT(1).getT(3);                    // project::Sweeten<NV>
		auto& wet_gain2 = this->getT(3).getT(1).getT(4);                  // core::gain<NV>
		auto& dry_wet2 = this->getT(4);                                   // Band_impl::dry_wet2_t<NV>
		auto& dry_path1 = this->getT(4).getT(0);                          // Band_impl::dry_path1_t<NV>
		auto& dry_wet_mixer1 = this->getT(4).getT(0).getT(0);             // Band_impl::dry_wet_mixer1_t<NV>
		auto& dry_gain1 = this->getT(4).getT(0).getT(1);                  // core::gain<NV>
		auto& wet_path1 = this->getT(4).getT(1);                          // Band_impl::wet_path1_t<NV>
		auto& branch1 = this->getT(4).getT(1).getT(0);                    // Band_impl::branch1_t<NV>
		auto& chain = this->getT(4).getT(1).getT(0).getT(0);              // Band_impl::chain_t<NV>
		auto& GrooveWear = this->getT(4).getT(1).getT(0).getT(0).getT(0); // project::GrooveWear<NV>
		auto& TapeDust = this->getT(4).getT(1).getT(0).getT(0).getT(1);   // project::TapeDust<NV>
		auto& Pockey2 = this->getT(4).getT(1).getT(0).getT(1);            // project::Pockey2<NV>
		auto& wet_gain1 = this->getT(4).getT(1).getT(1);                  // core::gain<NV>
		auto& ClipSoftly = this->getT(5);                                 // project::ClipSoftly<NV>
		
		// Parameter Connections -------------------------------------------------------------------
		
		dry_wet3.getParameterT(0).connectT(0, dry_wet_mixer2); // DryWet -> dry_wet_mixer2::Value
		dry_wet2.getParameterT(0).connectT(0, dry_wet_mixer1); // DryWet -> dry_wet_mixer1::Value
		auto& Tube_p = this->getParameterT(0);
		Tube_p.connectT(0, Tube2); // Tube -> Tube2::Tube
		Tube_p.connectT(1, Tube3); // Tube -> Tube3::Tube
		
		this->getParameterT(1).connectT(0, dry_wet3); // Tape -> dry_wet3::DryWet
		
		this->getParameterT(2).connectT(0, Tape); // Tape_Slam -> Tape::Slam
		
		this->getParameterT(3).connectT(0, Tape); // Tape_Bump -> Tape::Bump
		
		this->getParameterT(4).connectT(0, IronOxide5); // Tape_high -> IronOxide5::TapeHigh
		
		this->getParameterT(5).connectT(0, low_invert); // Tape_low -> low_invert::Value
		
		auto& Flutter_p = this->getParameterT(6);
		Flutter_p.connectT(0, IronOxide5); // Flutter -> IronOxide5::Flutter
		Flutter_p.connectT(1, Flutter);    // Flutter -> Flutter::Flutter
		
		this->getParameterT(7).connectT(0, IronOxide5); // Tape_noise -> IronOxide5::Noise
		
		this->getParameterT(8).connectT(0, Sweeten); // Tape_Sweeten -> Sweeten::Sweeten
		
		this->getParameterT(9).connectT(0, branch1); // Textures_Mode -> branch1::Index
		
		this->getParameterT(10).connectT(0, GrooveWear); // Textures_Wear -> GrooveWear::Wear
		
		this->getParameterT(11).connectT(0, TapeDust); // Textures_Dust -> TapeDust::Dust
		
		this->getParameterT(12).connectT(0, Pockey2); // Textures_Freq -> Pockey2::DeFreq
		
		this->getParameterT(13).connectT(0, Pockey2); // Textures_Rez -> Pockey2::DeRez
		
		this->getParameterT(14).connectT(0, dry_wet2); // Textures -> dry_wet2::DryWet
		
		// Modulation Connections ------------------------------------------------------------------
		
		low_invert.getWrappedObject().getParameter().connectT(0, IronOxide5); // low_invert -> IronOxide5::TapeLow
		auto& dry_wet_mixer2_p = dry_wet_mixer2.getWrappedObject().getParameter();
		dry_wet_mixer2_p.getParameterT(0).connectT(0, dry_gain2); // dry_wet_mixer2 -> dry_gain2::Gain
		dry_wet_mixer2_p.getParameterT(1).connectT(0, wet_gain2); // dry_wet_mixer2 -> wet_gain2::Gain
		auto& dry_wet_mixer1_p = dry_wet_mixer1.getWrappedObject().getParameter();
		dry_wet_mixer1_p.getParameterT(0).connectT(0, dry_gain1); // dry_wet_mixer1 -> dry_gain1::Gain
		dry_wet_mixer1_p.getParameterT(1).connectT(0, wet_gain1); // dry_wet_mixer1 -> wet_gain1::Gain
		
		// Default Values --------------------------------------------------------------------------
		
		;                                 // low_invert::Value is automated
		low_invert.setParameterT(1, -1.); // control::pma::Multiply
		low_invert.setParameterT(2, 1.);  // control::pma::Add
		
		Tube2.setParameterT(0, 0.502125); // project::Tube2::Input
		;                                 // Tube2::Tube is automated
		
		Tube3.setParameterT(0, 0.498662); // project::Tube2::Input
		;                                 // Tube3::Tube is automated
		
		; // dry_wet3::DryWet is automated
		
		; // dry_wet_mixer2::Value is automated
		
		;                                // dry_gain2::Gain is automated
		dry_gain2.setParameterT(1, 20.); // core::gain::Smoothing
		dry_gain2.setParameterT(2, 0.);  // core::gain::ResetValue
		
		; // Tape::Slam is automated
		; // Tape::Bump is automated
		
		IronOxide5.setParameterT(0, 0.5); // project::IronOxide5::InputTrim
		;                                 // IronOxide5::TapeHigh is automated
		;                                 // IronOxide5::TapeLow is automated
		;                                 // IronOxide5::Flutter is automated
		;                                 // IronOxide5::Noise is automated
		IronOxide5.setParameterT(5, 0.5); // project::IronOxide5::OutputTrim
		IronOxide5.setParameterT(6, 1.);  // project::IronOxide5::InvDryWet
		
		; // Flutter::Flutter is automated
		
		; // Sweeten::Sweeten is automated
		
		;                                // wet_gain2::Gain is automated
		wet_gain2.setParameterT(1, 20.); // core::gain::Smoothing
		wet_gain2.setParameterT(2, 0.);  // core::gain::ResetValue
		
		; // dry_wet2::DryWet is automated
		
		; // dry_wet_mixer1::Value is automated
		
		;                                // dry_gain1::Gain is automated
		dry_gain1.setParameterT(1, 20.); // core::gain::Smoothing
		dry_gain1.setParameterT(2, 0.);  // core::gain::ResetValue
		
		; // branch1::Index is automated
		
		;                                // GrooveWear::Wear is automated
		GrooveWear.setParameterT(1, 1.); // project::GrooveWear::DryWet
		
		;                              // TapeDust::Dust is automated
		TapeDust.setParameterT(1, 1.); // project::TapeDust::DryWet
		
		;                             // Pockey2::DeFreq is automated
		;                             // Pockey2::DeRez is automated
		Pockey2.setParameterT(2, 1.); // project::Pockey2::DryWet
		
		;                                // wet_gain1::Gain is automated
		wet_gain1.setParameterT(1, 20.); // core::gain::Smoothing
		wet_gain1.setParameterT(2, 0.);  // core::gain::ResetValue
		
		this->setParameterT(0, 0.);
		this->setParameterT(1, 1.);
		this->setParameterT(2, 0.);
		this->setParameterT(3, 0.617368);
		this->setParameterT(4, 1.);
		this->setParameterT(5, 0.559179);
		this->setParameterT(6, 0.);
		this->setParameterT(7, 0.);
		this->setParameterT(8, 0.000283936);
		this->setParameterT(9, 1.);
		this->setParameterT(10, 0.503714);
		this->setParameterT(11, 0.);
		this->setParameterT(12, 1.);
		this->setParameterT(13, 0.722735);
		this->setParameterT(14, 1.);
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


