#pragma once

#include "Tube2.h"
#include "Tube2.h"
#include "Tape.h"
#include "IronOxide5.h"
#include "Flutter.h"
#include "Sweeten.h"
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
using HOT_t_ = container::chain<parameter::empty, 
                                wrap::fix<2, project::SoftClipper<NV>>>;

template <int NV>
using HOT_t = bypass::smoothed<20, HOT_t_<NV>>;

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

DECLARE_PARAMETER_RANGE_SKEW(dry_wet_mixer_c0Range, 
                             -100., 
                             0., 
                             5.42227);

template <int NV>
using dry_wet_mixer_c0 = parameter::from0To1<core::gain<NV>, 
                                             0, 
                                             dry_wet_mixer_c0Range>;

template <int NV> using dry_wet_mixer_c1 = dry_wet_mixer_c0<NV>;

template <int NV>
using dry_wet_mixer_multimod = parameter::list<dry_wet_mixer_c0<NV>, dry_wet_mixer_c1<NV>>;

template <int NV>
using dry_wet_mixer_t = control::xfader<dry_wet_mixer_multimod<NV>, 
                                        faders::cosine_half>;

template <int NV>
using dry_path_t = container::chain<parameter::empty, 
                                    wrap::fix<2, dry_wet_mixer_t<NV>>, 
                                    core::gain<NV>>;

template <int NV>
using minmax1_t = control::minmax<NV, 
                                  parameter::plain<project::SoftClipper<NV>, 0>>;

template <int NV>
using modchain2_t_ = container::chain<parameter::empty, 
                                      wrap::fix<1, minmax1_t<NV>>>;

template <int NV>
using modchain2_t = wrap::control_rate<modchain2_t_<NV>>;

template <int NV>
using wet_path_t = container::chain<parameter::empty, 
                                    wrap::fix<2, modchain2_t<NV>>, 
                                    project::SoftClipper<NV>, 
                                    core::gain<NV>, 
                                    core::gain<NV>>;

namespace dry_wet1_t_parameters
{

template <int NV>
using DryWet = parameter::chain<ranges::Identity, 
                                parameter::plain<Band_impl::dry_wet_mixer_t<NV>, 0>, 
                                parameter::plain<Band_impl::minmax1_t<NV>, 0>>;

}

template <int NV>
using dry_wet1_t = container::split<dry_wet1_t_parameters::DryWet<NV>, 
                                    wrap::fix<2, dry_path_t<NV>>, 
                                    wet_path_t<NV>>;

template <int NV>
using Saturation_t = container::chain<parameter::empty, 
                                      wrap::fix<2, modchain_t<NV>>, 
                                      project::Tube2<NV>, 
                                      project::Tube2<NV>, 
                                      dry_wet1_t<NV>>;

template <int NV> using dry_wet_mixer2_c0 = dry_wet_mixer_c0<NV>;

template <int NV> using dry_wet_mixer2_c1 = dry_wet_mixer_c0<NV>;

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

DECLARE_PARAMETER_RANGE_SKEW(pma_modRange, 
                             -100., 
                             6., 
                             5.42227);

template <int NV>
using pma_mod = parameter::from0To1<core::gain<NV>, 
                                    0, 
                                    pma_modRange>;

template <int NV>
using pma_t = control::pma<NV, pma_mod<NV>>;
template <int NV>
using minmax2_t = control::minmax<NV, 
                                  parameter::plain<pma_t<NV>, 0>>;

template <int NV>
using modchain1_t_ = container::chain<parameter::empty, 
                                      wrap::fix<1, low_invert_t<NV>>, 
                                      control::minmax<NV, parameter::empty>, 
                                      minmax2_t<NV>, 
                                      pma_t<NV>>;

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
                              parameter::plain<Band_impl::tubeinputminmax_t<NV>, 0>, 
                              parameter::plain<Band_impl::dry_wet1_t<NV>, 0>>;

template <int NV>
using Tape_Slam = parameter::chain<ranges::Identity, 
                                   parameter::plain<project::Tape<NV>, 0>, 
                                   parameter::plain<Band_impl::minmax2_t<NV>, 0>>;

template <int NV>
using Flutter = parameter::chain<ranges::Identity, 
                                 parameter::plain<project::IronOxide5<NV>, 3>, 
                                 parameter::plain<project::Flutter<NV>, 0>>;

template <int NV>
using Hot = parameter::bypass<Band_impl::HOT_t<NV>>;

template <int NV>
using Tape = parameter::plain<Band_impl::TapeDryWet_t<NV>, 
                              0>;
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
using Tape_Sweeten = parameter::plain<wrap::no_process<project::Sweeten<NV>>, 
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
                                     Hot<NV>>;
}

template <int NV>
using Band_t_ = container::chain<Band_t_parameters::Band_t_plist<NV>, 
                                 wrap::fix<2, HOT_t<NV>>, 
                                 Saturation_t<NV>, 
                                 TapeDryWet_t<NV>, 
                                 wrap::no_process<project::Sweeten<NV>>, 
                                 project::SoftClipper<NV>>;

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
		SNEX_METADATA_ENCODED_PARAMETERS(168)
		{
			0x005B, 0x0000, 0x5400, 0x6275, 0x0065, 0x0000, 0x0000, 0x0000, 
            0x3F80, 0x0000, 0x0000, 0x0000, 0x3F80, 0x0000, 0x0000, 0x015B, 
            0x0000, 0x5400, 0x7061, 0x0065, 0x0000, 0x0000, 0x0000, 0x3F80, 
            0xD0B9, 0x3EE2, 0x0000, 0x3F80, 0x0000, 0x0000, 0x025B, 0x0000, 
            0x5400, 0x7061, 0x5F65, 0x6C53, 0x6D61, 0x0000, 0x0000, 0x0000, 
            0x8000, 0xFF3F, 0x4E52, 0x003F, 0x8000, 0x003F, 0x0000, 0x5B00, 
            0x0003, 0x0000, 0x6154, 0x6570, 0x425F, 0x6D75, 0x0070, 0x0000, 
            0x0000, 0x0000, 0x3F80, 0x0000, 0x0000, 0x0000, 0x3F80, 0x0000, 
            0x0000, 0x045B, 0x0000, 0x5400, 0x7061, 0x5F65, 0x6968, 0x6867, 
            0x0000, 0x0000, 0x0000, 0x8000, 0xCB3F, 0x0051, 0x003F, 0x8000, 
            0x003F, 0x0000, 0x5B00, 0x0005, 0x0000, 0x6154, 0x6570, 0x6C5F, 
            0x776F, 0x0000, 0x0000, 0x0000, 0x8000, 0x063F, 0x0091, 0x003F, 
            0x8000, 0x003F, 0x0000, 0x5B00, 0x0006, 0x0000, 0x6C46, 0x7475, 
            0x6574, 0x0072, 0x0000, 0x0000, 0x0000, 0x3F80, 0x0000, 0x0000, 
            0x0000, 0x3F80, 0x0000, 0x0000, 0x075B, 0x0000, 0x5400, 0x7061, 
            0x5F65, 0x6F6E, 0x7369, 0x0065, 0x0000, 0x0000, 0x0000, 0x3F80, 
            0x0000, 0x0000, 0x0000, 0x3F80, 0x0000, 0x0000, 0x085B, 0x0000, 
            0x5400, 0x7061, 0x5F65, 0x7753, 0x6565, 0x6574, 0x006E, 0x0000, 
            0x0000, 0x0000, 0x3F80, 0x0000, 0x0000, 0x0000, 0x3F80, 0x0000, 
            0x0000, 0x095B, 0x0000, 0x4800, 0x746F, 0x0000, 0x0000, 0x0000, 
            0x8000, 0x003F, 0x0000, 0x0000, 0x8000, 0x003F, 0x8000, 0x003F
		};
	};
	
	instance()
	{
		// Node References -------------------------------------------------------------------------
		
		auto& HOT = this->getT(0);                                     // Band_impl::HOT_t<NV>
		auto& faust1 = this->getT(0).getT(0);                          // project::SoftClipper<NV>
		auto& Saturation = this->getT(1);                              // Band_impl::Saturation_t<NV>
		auto& modchain = this->getT(1).getT(0);                        // Band_impl::modchain_t<NV>
		auto& split = this->getT(1).getT(0).getT(0);                   // Band_impl::split_t<NV>
		auto& tubeinputminmax = this->getT(1).getT(0).getT(0).getT(0); // Band_impl::tubeinputminmax_t<NV>
		auto& Tube2 = this->getT(1).getT(1);                           // project::Tube2<NV>
		auto& Tube3 = this->getT(1).getT(2);                           // project::Tube2<NV>
		auto& dry_wet1 = this->getT(1).getT(3);                        // Band_impl::dry_wet1_t<NV>
		auto& dry_path = this->getT(1).getT(3).getT(0);                // Band_impl::dry_path_t<NV>
		auto& dry_wet_mixer = this->getT(1).getT(3).getT(0).getT(0);   // Band_impl::dry_wet_mixer_t<NV>
		auto& dry_gain = this->getT(1).getT(3).getT(0).getT(1);        // core::gain<NV>
		auto& wet_path = this->getT(1).getT(3).getT(1);                // Band_impl::wet_path_t<NV>
		auto& modchain2 = this->getT(1).getT(3).getT(1).getT(0);       // Band_impl::modchain2_t<NV>
		auto& minmax1 = this->getT(1).getT(3).getT(1).getT(0).getT(0); // Band_impl::minmax1_t<NV>
		auto& faust2 = this->getT(1).getT(3).getT(1).getT(1);          // project::SoftClipper<NV>
		auto& gain = this->getT(1).getT(3).getT(1).getT(2);            // core::gain<NV>
		auto& wet_gain = this->getT(1).getT(3).getT(1).getT(3);        // core::gain<NV>
		auto& TapeDryWet = this->getT(2);                              // Band_impl::TapeDryWet_t<NV>
		auto& dry_path2 = this->getT(2).getT(0);                       // Band_impl::dry_path2_t<NV>
		auto& dry_wet_mixer2 = this->getT(2).getT(0).getT(0);          // Band_impl::dry_wet_mixer2_t<NV>
		auto& dry_gain2 = this->getT(2).getT(0).getT(1);               // core::gain<NV>
		auto& wet_path2 = this->getT(2).getT(1);                       // Band_impl::wet_path2_t<NV>
		auto& modchain1 = this->getT(2).getT(1).getT(0);               // Band_impl::modchain1_t<NV>
		auto& low_invert = this->getT(2).getT(1).getT(0).getT(0);      // Band_impl::low_invert_t<NV>
		auto& minmax = this->getT(2).getT(1).getT(0).getT(1);          // control::minmax<NV, parameter::empty>
		auto& minmax2 = this->getT(2).getT(1).getT(0).getT(2);         // Band_impl::minmax2_t<NV>
		auto& pma = this->getT(2).getT(1).getT(0).getT(3);             // Band_impl::pma_t<NV>
		auto& Tape2 = this->getT(2).getT(1).getT(1);                   // project::Tape<NV>
		auto& SlamGainMatcher = this->getT(2).getT(1).getT(2);         // core::gain<NV>
		auto& IronOxide5 = this->getT(2).getT(1).getT(3);              // project::IronOxide5<NV>
		auto& Flutter = this->getT(2).getT(1).getT(4);                 // project::Flutter<NV>
		auto& wet_gain2 = this->getT(2).getT(1).getT(5);               // core::gain<NV>
		auto& Sweeten = this->getT(3);                                 // wrap::no_process<project::Sweeten<NV>>
		auto& faust = this->getT(4);                                   // project::SoftClipper<NV>
		
		// Parameter Connections -------------------------------------------------------------------
		
		auto& DryWet_p = dry_wet1.getParameterT(0);
		DryWet_p.connectT(0, dry_wet_mixer);                     // DryWet -> dry_wet_mixer::Value
		DryWet_p.connectT(1, minmax1);                           // DryWet -> minmax1::Value
		TapeDryWet.getParameterT(0).connectT(0, dry_wet_mixer2); // DryWet -> dry_wet_mixer2::Value
		auto& Tube_p = this->getParameterT(0);
		Tube_p.connectT(0, Tube2);           // Tube -> Tube2::Tube
		Tube_p.connectT(1, Tube3);           // Tube -> Tube3::Tube
		Tube_p.connectT(2, tubeinputminmax); // Tube -> tubeinputminmax::Value
		Tube_p.connectT(3, dry_wet1);        // Tube -> dry_wet1::DryWet
		
		this->getParameterT(1).connectT(0, TapeDryWet); // Tape -> TapeDryWet::DryWet
		
		auto& Tape_Slam_p = this->getParameterT(2);
		Tape_Slam_p.connectT(0, Tape2);   // Tape_Slam -> Tape2::Slam
		Tape_Slam_p.connectT(1, minmax2); // Tape_Slam -> minmax2::Value
		
		this->getParameterT(3).connectT(0, Tape2); // Tape_Bump -> Tape2::Bump
		
		this->getParameterT(4).connectT(0, IronOxide5); // Tape_high -> IronOxide5::TapeHigh
		
		this->getParameterT(5).connectT(0, low_invert); // Tape_low -> low_invert::Value
		
		auto& Flutter_p = this->getParameterT(6);
		Flutter_p.connectT(0, IronOxide5); // Flutter -> IronOxide5::Flutter
		Flutter_p.connectT(1, Flutter);    // Flutter -> Flutter::Flutter
		
		this->getParameterT(7).connectT(0, IronOxide5); // Tape_noise -> IronOxide5::Noise
		
		this->getParameterT(8).connectT(0, Sweeten); // Tape_Sweeten -> Sweeten::Sweeten
		
		this->getParameterT(9).connectT(0, HOT); // Hot -> HOT::Bypassed
		
		// Modulation Connections ------------------------------------------------------------------
		
		tubeinputminmax.getWrappedObject().getParameter().connectT(0, Tube2); // tubeinputminmax -> Tube2::Input
		tubeinputminmax.getWrappedObject().getParameter().connectT(1, Tube3); // tubeinputminmax -> Tube3::Input
		auto& dry_wet_mixer_p = dry_wet_mixer.getWrappedObject().getParameter();
		dry_wet_mixer_p.getParameterT(0).connectT(0, dry_gain);        // dry_wet_mixer -> dry_gain::Gain
		dry_wet_mixer_p.getParameterT(1).connectT(0, wet_gain);        // dry_wet_mixer -> wet_gain::Gain
		minmax1.getWrappedObject().getParameter().connectT(0, faust2); // minmax1 -> faust2::Drive
		auto& dry_wet_mixer2_p = dry_wet_mixer2.getWrappedObject().getParameter();
		dry_wet_mixer2_p.getParameterT(0).connectT(0, dry_gain2);             // dry_wet_mixer2 -> dry_gain2::Gain
		dry_wet_mixer2_p.getParameterT(1).connectT(0, wet_gain2);             // dry_wet_mixer2 -> wet_gain2::Gain
		low_invert.getWrappedObject().getParameter().connectT(0, IronOxide5); // low_invert -> IronOxide5::TapeLow
		pma.getWrappedObject().getParameter().connectT(0, SlamGainMatcher);   // pma -> SlamGainMatcher::Gain
		minmax2.getWrappedObject().getParameter().connectT(0, pma);           // minmax2 -> pma::Value
		
		// Default Values --------------------------------------------------------------------------
		
		faust1.setParameterT(0, 0.15);         // core::faust::Drive
		faust1.setParameterT(1, -2.23517e-08); // core::faust::Offset
		
		;                                           // tubeinputminmax::Value is automated
		tubeinputminmax.setParameterT(1, 0.497614); // control::minmax::Minimum
		tubeinputminmax.setParameterT(2, 0.343532); // control::minmax::Maximum
		tubeinputminmax.setParameterT(3, 0.115888); // control::minmax::Skew
		tubeinputminmax.setParameterT(4, 0.);       // control::minmax::Step
		tubeinputminmax.setParameterT(5, 0.);       // control::minmax::Polarity
		
		; // Tube2::Input is automated
		; // Tube2::Tube is automated
		
		; // Tube3::Input is automated
		; // Tube3::Tube is automated
		
		; // dry_wet1::DryWet is automated
		
		; // dry_wet_mixer::Value is automated
		
		;                               // dry_gain::Gain is automated
		dry_gain.setParameterT(1, 20.); // core::gain::Smoothing
		dry_gain.setParameterT(2, 0.);  // core::gain::ResetValue
		
		;                                   // minmax1::Value is automated
		minmax1.setParameterT(1, 0.099355); // control::minmax::Minimum
		minmax1.setParameterT(2, 0.424176); // control::minmax::Maximum
		minmax1.setParameterT(3, 0.574959); // control::minmax::Skew
		minmax1.setParameterT(4, 0.);       // control::minmax::Step
		minmax1.setParameterT(5, 0.);       // control::minmax::Polarity
		
		;                                      // faust2::Drive is automated
		faust2.setParameterT(1, -2.23517e-08); // core::faust::Offset
		
		gain.setParameterT(0, 3.6); // core::gain::Gain
		gain.setParameterT(1, 20.); // core::gain::Smoothing
		gain.setParameterT(2, 0.);  // core::gain::ResetValue
		
		;                               // wet_gain::Gain is automated
		wet_gain.setParameterT(1, 20.); // core::gain::Smoothing
		wet_gain.setParameterT(2, 0.);  // core::gain::ResetValue
		
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
		
		;                                   // minmax2::Value is automated
		minmax2.setParameterT(1, 0.368116); // control::minmax::Minimum
		minmax2.setParameterT(2, 0.90315);  // control::minmax::Maximum
		minmax2.setParameterT(3, 0.518337); // control::minmax::Skew
		minmax2.setParameterT(4, 0.);       // control::minmax::Step
		minmax2.setParameterT(5, 1.);       // control::minmax::Polarity
		
		;                         // pma::Value is automated
		pma.setParameterT(1, 1.); // control::pma::Multiply
		pma.setParameterT(2, 0.); // control::pma::Add
		
		; // Tape2::Slam is automated
		; // Tape2::Bump is automated
		
		;                                      // SlamGainMatcher::Gain is automated
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
		
		faust.setParameterT(0, 0.04); // core::faust::Drive
		faust.setParameterT(1, 0.);   // core::faust::Offset
		
		this->setParameterT(0, 0.);
		this->setParameterT(1, 0.442999);
		this->setParameterT(2, 0.805954);
		this->setParameterT(3, 0.);
		this->setParameterT(4, 0.501248);
		this->setParameterT(5, 0.502213);
		this->setParameterT(6, 0.);
		this->setParameterT(7, 0.);
		this->setParameterT(8, 0.);
		this->setParameterT(9, 0.);
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


