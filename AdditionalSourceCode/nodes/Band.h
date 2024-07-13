#pragma once

#include "Tube2.h"
#include "Tube2.h"
#include "Tape.h"
#include "IronOxide5.h"
#include "Flutter.h"
#include "Sweeten.h"
#include "ClipSoftly.h"
#include "Tube2.h"
#include "Tube2.h"
#include "Tape.h"
#include "IronOxide5.h"
#include "Flutter.h"
#include "Sweeten.h"
#include "ClipSoftly.h"
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
using tubeinputminmax_mod = parameter::chain<ranges::Identity, 
                                             parameter::plain<project::Tube2<NV>, 0>, 
                                             parameter::plain<project::Tube2<NV>, 0>, 
                                             parameter::plain<project::Tube2<NV>, 0>, 
                                             parameter::plain<project::Tube2<NV>, 0>, 
                                             parameter::plain<project::Tube2<NV>, 0>, 
                                             parameter::plain<project::Tube2<NV>, 0>>;

template <int NV>
using tubeinputminmax_t = control::minmax<NV, 
                                          tubeinputminmax_mod<NV>>;

template <int NV>
using Tubesmoother_mod = parameter::chain<ranges::Identity, 
                                          parameter::plain<project::Tube2<NV>, 1>, 
                                          parameter::plain<project::Tube2<NV>, 1>, 
                                          parameter::plain<project::Tube2<NV>, 1>, 
                                          parameter::plain<project::Tube2<NV>, 1>, 
                                          parameter::plain<tubeinputminmax_t<NV>, 0>, 
                                          parameter::plain<project::Tube2<NV>, 1>, 
                                          parameter::plain<project::Tube2<NV>, 1>>;

template <int NV>
using Tubesmoother_t = wrap::mod<Tubesmoother_mod<NV>, 
                                 control::smoothed_parameter<NV, smoothers::linear_ramp<NV>>>;

template <int NV>
using TapeSmootherSlam_mod = parameter::chain<ranges::Identity, 
                                              parameter::plain<project::Tape<NV>, 0>, 
                                              parameter::plain<project::Tape<NV>, 0>, 
                                              parameter::plain<project::Tape<NV>, 0>>;

template <int NV>
using TapeSmootherSlam_t = wrap::mod<TapeSmootherSlam_mod<NV>, 
                                     control::smoothed_parameter<NV, smoothers::linear_ramp<NV>>>;

template <int NV>
using split1_t = container::split<parameter::empty, 
                                  wrap::fix<1, Tubesmoother_t<NV>>, 
                                  TapeSmootherSlam_t<NV>>;

template <int NV>
using modchain2_t_ = container::chain<parameter::empty, 
                                      wrap::fix<1, split1_t<NV>>>;

template <int NV>
using modchain2_t = wrap::control_rate<modchain2_t_<NV>>;

template <int NV>
using minmax1_t = control::minmax<NV, 
                                  parameter::plain<core::gain<NV>, 0>>;

template <int NV>
using split_t = container::split<parameter::empty, 
                                 wrap::fix<1, tubeinputminmax_t<NV>>>;

template <int NV>
using modchain_t_ = container::chain<parameter::empty, 
                                     wrap::fix<1, split_t<NV>>>;

template <int NV>
using modchain_t = wrap::control_rate<modchain_t_<NV>>;

template <int NV>
using low_invert_mod = parameter::chain<ranges::Identity, 
                                        parameter::plain<project::IronOxide5<NV>, 2>, 
                                        parameter::plain<project::IronOxide5<NV>, 2>, 
                                        parameter::plain<project::IronOxide5<NV>, 2>>;

template <int NV>
using low_invert_t = control::pma<NV, low_invert_mod<NV>>;

template <int NV>
using modchain1_t_ = container::chain<parameter::empty, 
                                      wrap::fix<1, low_invert_t<NV>>>;

template <int NV>
using modchain1_t = wrap::control_rate<modchain1_t_<NV>>;

template <int NV>
using Saturation2_t = container::chain<parameter::empty, 
                                       wrap::fix<2, project::Tube2<NV>>, 
                                       project::Tube2<NV>>;

DECLARE_PARAMETER_RANGE_SKEW(dry_wet_mixer4_c0Range, 
                             -100., 
                             0., 
                             5.42227);

template <int NV>
using dry_wet_mixer4_c0 = parameter::from0To1<core::gain<NV>, 
                                              0, 
                                              dry_wet_mixer4_c0Range>;

template <int NV> using dry_wet_mixer4_c1 = dry_wet_mixer4_c0<NV>;

template <int NV>
using dry_wet_mixer4_multimod = parameter::list<dry_wet_mixer4_c0<NV>, dry_wet_mixer4_c1<NV>>;

template <int NV>
using dry_wet_mixer4_t = control::xfader<dry_wet_mixer4_multimod<NV>, 
                                         faders::cosine_half>;

template <int NV>
using dry_path4_t = container::chain<parameter::empty, 
                                     wrap::fix<2, dry_wet_mixer4_t<NV>>, 
                                     core::gain<NV>>;

template <int NV>
using wet_path4_t = container::chain<parameter::empty, 
                                     wrap::fix<2, project::Tape<NV>>, 
                                     project::IronOxide5<NV>, 
                                     project::Flutter<NV>, 
                                     core::gain<NV>>;

namespace TapeDryWet2_t_parameters
{
}

template <int NV>
using TapeDryWet2_t = container::split<parameter::plain<Band_impl::dry_wet_mixer4_t<NV>, 0>, 
                                       wrap::fix<2, dry_path4_t<NV>>, 
                                       wet_path4_t<NV>>;

template <int NV>
using chain_t = container::chain<parameter::empty, 
                                 wrap::fix<2, Saturation2_t<NV>>, 
                                 TapeDryWet2_t<NV>, 
                                 project::Sweeten<NV>, 
                                 project::ClipSoftly<NV>>;

template <int NV> using Saturation_t = Saturation2_t<NV>;

template <int NV> using dry_wet_mixer2_c0 = dry_wet_mixer4_c0<NV>;

template <int NV> using dry_wet_mixer2_c1 = dry_wet_mixer4_c0<NV>;

template <int NV>
using dry_wet_mixer2_multimod = parameter::list<dry_wet_mixer2_c0<NV>, dry_wet_mixer2_c1<NV>>;

template <int NV>
using dry_wet_mixer2_t = control::xfader<dry_wet_mixer2_multimod<NV>, 
                                         faders::cosine_half>;

template <int NV>
using dry_path2_t = container::chain<parameter::empty, 
                                     wrap::fix<2, dry_wet_mixer2_t<NV>>, 
                                     core::gain<NV>>;

template <int NV> using wet_path2_t = wet_path4_t<NV>;

namespace TapeDryWet_t_parameters
{
}

template <int NV>
using TapeDryWet_t = container::split<parameter::plain<Band_impl::dry_wet_mixer2_t<NV>, 0>, 
                                      wrap::fix<2, dry_path2_t<NV>>, 
                                      wet_path2_t<NV>>;

template <int NV>
using oversample2x_t_ = container::chain<parameter::empty, 
                                         wrap::fix<2, Saturation_t<NV>>, 
                                         TapeDryWet_t<NV>, 
                                         project::Sweeten<NV>, 
                                         project::ClipSoftly<NV>>;

template <int NV>
using oversample2x_t = wrap::oversample<2, oversample2x_t_<NV>>;

template <int NV> using Saturation1_t = Saturation2_t<NV>;

template <int NV> using dry_wet_mixer3_c0 = dry_wet_mixer4_c0<NV>;

template <int NV> using dry_wet_mixer3_c1 = dry_wet_mixer4_c0<NV>;

template <int NV>
using dry_wet_mixer3_multimod = parameter::list<dry_wet_mixer3_c0<NV>, dry_wet_mixer3_c1<NV>>;

template <int NV>
using dry_wet_mixer3_t = control::xfader<dry_wet_mixer3_multimod<NV>, 
                                         faders::cosine_half>;

template <int NV>
using dry_path3_t = container::chain<parameter::empty, 
                                     wrap::fix<2, dry_wet_mixer3_t<NV>>, 
                                     core::gain<NV>>;

template <int NV> using wet_path3_t = wet_path4_t<NV>;

namespace TapeDryWet1_t_parameters
{
}

template <int NV>
using TapeDryWet1_t = container::split<parameter::plain<Band_impl::dry_wet_mixer3_t<NV>, 0>, 
                                       wrap::fix<2, dry_path3_t<NV>>, 
                                       wet_path3_t<NV>>;

template <int NV>
using oversample4x_t_ = container::chain<parameter::empty, 
                                         wrap::fix<2, Saturation1_t<NV>>, 
                                         TapeDryWet1_t<NV>, 
                                         project::Sweeten<NV>, 
                                         project::ClipSoftly<NV>>;

template <int NV>
using oversample4x_t = wrap::oversample<4, oversample4x_t_<NV>>;
template <int NV>
using branch_t = container::branch<parameter::empty, 
                                   wrap::fix<2, chain_t<NV>>, 
                                   oversample2x_t<NV>, 
                                   oversample4x_t<NV>>;

namespace Band_t_parameters
{
// Parameter list for Band_impl::Band_t ------------------------------------------------------------

template <int NV>
using Tape = parameter::chain<ranges::Identity, 
                              parameter::plain<Band_impl::TapeDryWet_t<NV>, 0>, 
                              parameter::plain<Band_impl::TapeDryWet2_t<NV>, 0>, 
                              parameter::plain<Band_impl::TapeDryWet1_t<NV>, 0>>;

template <int NV>
using Tape_high = parameter::chain<ranges::Identity, 
                                   parameter::plain<project::IronOxide5<NV>, 1>, 
                                   parameter::plain<project::IronOxide5<NV>, 1>, 
                                   parameter::plain<project::IronOxide5<NV>, 1>>;

template <int NV>
using Flutter = parameter::chain<ranges::Identity, 
                                 parameter::plain<project::IronOxide5<NV>, 3>, 
                                 parameter::plain<project::IronOxide5<NV>, 3>, 
                                 parameter::plain<project::IronOxide5<NV>, 3>, 
                                 parameter::plain<project::Flutter<NV>, 0>, 
                                 parameter::plain<project::Flutter<NV>, 0>, 
                                 parameter::plain<project::Flutter<NV>, 0>>;

template <int NV>
using Tape_noise = parameter::chain<ranges::Identity, 
                                    parameter::plain<project::IronOxide5<NV>, 4>, 
                                    parameter::plain<project::IronOxide5<NV>, 4>, 
                                    parameter::plain<project::IronOxide5<NV>, 4>>;

template <int NV>
using Tape_Sweeten = parameter::chain<ranges::Identity, 
                                      parameter::plain<project::Sweeten<NV>, 0>, 
                                      parameter::plain<project::Sweeten<NV>, 0>, 
                                      parameter::plain<project::Sweeten<NV>, 0>>;

template <int NV>
using Tube = parameter::plain<Band_impl::Tubesmoother_t<NV>, 
                              0>;
template <int NV>
using Tape_Slam = parameter::plain<Band_impl::TapeSmootherSlam_t<NV>, 
                                   0>;
template <int NV>
using Tape_low = parameter::plain<Band_impl::low_invert_t<NV>, 
                                  0>;
template <int NV>
using Hot = parameter::plain<Band_impl::minmax1_t<NV>, 
                             0>;
template <int NV>
using oversample = parameter::plain<Band_impl::branch_t<NV>, 
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
                                     Hot<NV>, 
                                     oversample<NV>>;
}

template <int NV>
using Band_t_ = container::chain<Band_t_parameters::Band_t_plist<NV>, 
                                 wrap::fix<2, modchain2_t<NV>>, 
                                 minmax1_t<NV>, 
                                 core::gain<NV>, 
                                 modchain_t<NV>, 
                                 modchain1_t<NV>, 
                                 branch_t<NV>>;

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
		SNEX_METADATA_ENCODED_PARAMETERS(170)
		{
			0x005B, 0x0000, 0x5400, 0x6275, 0x0065, 0x0000, 0x0000, 0x0000, 
            0x3F80, 0x0000, 0x0000, 0x0000, 0x3F80, 0x0000, 0x0000, 0x015B, 
            0x0000, 0x5400, 0x7061, 0x0065, 0x0000, 0x0000, 0x0000, 0x3F80, 
            0xC9D1, 0x3F35, 0x0000, 0x3F80, 0x0000, 0x0000, 0x025B, 0x0000, 
            0x5400, 0x7061, 0x5F65, 0x6C53, 0x6D61, 0x0000, 0x0000, 0x0000, 
            0x8000, 0xDF3F, 0xBB51, 0x003E, 0x8000, 0x003F, 0x0000, 0x5B00, 
            0x0003, 0x0000, 0x6154, 0x6570, 0x685F, 0x6769, 0x0068, 0x0000, 
            0x0000, 0x0000, 0x3F80, 0x51CB, 0x3F00, 0x0000, 0x3F80, 0x0000, 
            0x0000, 0x045B, 0x0000, 0x5400, 0x7061, 0x5F65, 0x6F6C, 0x0077, 
            0x0000, 0x0000, 0x0000, 0x3F80, 0x8D35, 0x3F4E, 0x0000, 0x3F80, 
            0x0000, 0x0000, 0x055B, 0x0000, 0x4600, 0x756C, 0x7474, 0x7265, 
            0x0000, 0x0000, 0x0000, 0x8000, 0x833F, 0x09F6, 0x003E, 0x8000, 
            0x003F, 0x0000, 0x5B00, 0x0006, 0x0000, 0x6154, 0x6570, 0x6E5F, 
            0x696F, 0x6573, 0x0000, 0x0000, 0x0000, 0x8000, 0xF03F, 0x67A2, 
            0x003F, 0x8000, 0x003F, 0x0000, 0x5B00, 0x0007, 0x0000, 0x6154, 
            0x6570, 0x535F, 0x6577, 0x7465, 0x6E65, 0x0000, 0x0000, 0x0000, 
            0x8000, 0x003F, 0x0000, 0x0000, 0x8000, 0x003F, 0x0000, 0x5B00, 
            0x0008, 0x0000, 0x6F48, 0x0074, 0x0000, 0x0000, 0x0000, 0x3F80, 
            0x0000, 0x0000, 0x0000, 0x3F80, 0x0000, 0x3F80, 0x095B, 0x0000, 
            0x6F00, 0x6576, 0x7372, 0x6D61, 0x6C70, 0x0065, 0x0000, 0x0000, 
            0x0000, 0x4000, 0x0000, 0x0000, 0x0000, 0x3F80, 0x0000, 0x3F80, 
            0x0000, 0x0000
		};
	};
	
	instance()
	{
		// Node References -------------------------------------------------------------------------
		
		auto& modchain2 = this->getT(0);                                      // Band_impl::modchain2_t<NV>
		auto& split1 = this->getT(0).getT(0);                                 // Band_impl::split1_t<NV>
		auto& Tubesmoother = this->getT(0).getT(0).getT(0);                   // Band_impl::Tubesmoother_t<NV>
		auto& TapeSmootherSlam = this->getT(0).getT(0).getT(1);               // Band_impl::TapeSmootherSlam_t<NV>
		auto& minmax1 = this->getT(1);                                        // Band_impl::minmax1_t<NV>
		auto& gain = this->getT(2);                                           // core::gain<NV>
		auto& modchain = this->getT(3);                                       // Band_impl::modchain_t<NV>
		auto& split = this->getT(3).getT(0);                                  // Band_impl::split_t<NV>
		auto& tubeinputminmax = this->getT(3).getT(0).getT(0);                // Band_impl::tubeinputminmax_t<NV>
		auto& modchain1 = this->getT(4);                                      // Band_impl::modchain1_t<NV>
		auto& low_invert = this->getT(4).getT(0);                             // Band_impl::low_invert_t<NV>
		auto& branch = this->getT(5);                                         // Band_impl::branch_t<NV>
		auto& chain = this->getT(5).getT(0);                                  // Band_impl::chain_t<NV>
		auto& Saturation2 = this->getT(5).getT(0).getT(0);                    // Band_impl::Saturation2_t<NV>
		auto& Tube6 = this->getT(5).getT(0).getT(0).getT(0);                  // project::Tube2<NV>
		auto& Tube7 = this->getT(5).getT(0).getT(0).getT(1);                  // project::Tube2<NV>
		auto& TapeDryWet2 = this->getT(5).getT(0).getT(1);                    // Band_impl::TapeDryWet2_t<NV>
		auto& dry_path4 = this->getT(5).getT(0).getT(1).getT(0);              // Band_impl::dry_path4_t<NV>
		auto& dry_wet_mixer4 = this->getT(5).getT(0).getT(1).getT(0).getT(0); // Band_impl::dry_wet_mixer4_t<NV>
		auto& dry_gain4 = this->getT(5).getT(0).getT(1).getT(0).getT(1);      // core::gain<NV>
		auto& wet_path4 = this->getT(5).getT(0).getT(1).getT(1);              // Band_impl::wet_path4_t<NV>
		auto& Tape4 = this->getT(5).getT(0).getT(1).getT(1).getT(0);          // project::Tape<NV>
		auto& IronOxide7 = this->getT(5).getT(0).getT(1).getT(1).getT(1);     // project::IronOxide5<NV>
		auto& Flutter2 = this->getT(5).getT(0).getT(1).getT(1).getT(2);       // project::Flutter<NV>
		auto& wet_gain4 = this->getT(5).getT(0).getT(1).getT(1).getT(3);      // core::gain<NV>
		auto& Sweeten2 = this->getT(5).getT(0).getT(2);                       // project::Sweeten<NV>
		auto& ClipSoftly2 = this->getT(5).getT(0).getT(3);                    // project::ClipSoftly<NV>
		auto& oversample2x = this->getT(5).getT(1);                           // Band_impl::oversample2x_t<NV>
		auto& Saturation = this->getT(5).getT(1).getT(0);                     // Band_impl::Saturation_t<NV>
		auto& Tube2 = this->getT(5).getT(1).getT(0).getT(0);                  // project::Tube2<NV>
		auto& Tube3 = this->getT(5).getT(1).getT(0).getT(1);                  // project::Tube2<NV>
		auto& TapeDryWet = this->getT(5).getT(1).getT(1);                     // Band_impl::TapeDryWet_t<NV>
		auto& dry_path2 = this->getT(5).getT(1).getT(1).getT(0);              // Band_impl::dry_path2_t<NV>
		auto& dry_wet_mixer2 = this->getT(5).getT(1).getT(1).getT(0).getT(0); // Band_impl::dry_wet_mixer2_t<NV>
		auto& dry_gain2 = this->getT(5).getT(1).getT(1).getT(0).getT(1);      // core::gain<NV>
		auto& wet_path2 = this->getT(5).getT(1).getT(1).getT(1);              // Band_impl::wet_path2_t<NV>
		auto& Tape2 = this->getT(5).getT(1).getT(1).getT(1).getT(0);          // project::Tape<NV>
		auto& IronOxide5 = this->getT(5).getT(1).getT(1).getT(1).getT(1);     // project::IronOxide5<NV>
		auto& Flutter = this->getT(5).getT(1).getT(1).getT(1).getT(2);        // project::Flutter<NV>
		auto& wet_gain2 = this->getT(5).getT(1).getT(1).getT(1).getT(3);      // core::gain<NV>
		auto& Sweeten = this->getT(5).getT(1).getT(2);                        // project::Sweeten<NV>
		auto& ClipSoftly = this->getT(5).getT(1).getT(3);                     // project::ClipSoftly<NV>
		auto& oversample4x = this->getT(5).getT(2);                           // Band_impl::oversample4x_t<NV>
		auto& Saturation1 = this->getT(5).getT(2).getT(0);                    // Band_impl::Saturation1_t<NV>
		auto& Tube4 = this->getT(5).getT(2).getT(0).getT(0);                  // project::Tube2<NV>
		auto& Tube5 = this->getT(5).getT(2).getT(0).getT(1);                  // project::Tube2<NV>
		auto& TapeDryWet1 = this->getT(5).getT(2).getT(1);                    // Band_impl::TapeDryWet1_t<NV>
		auto& dry_path3 = this->getT(5).getT(2).getT(1).getT(0);              // Band_impl::dry_path3_t<NV>
		auto& dry_wet_mixer3 = this->getT(5).getT(2).getT(1).getT(0).getT(0); // Band_impl::dry_wet_mixer3_t<NV>
		auto& dry_gain3 = this->getT(5).getT(2).getT(1).getT(0).getT(1);      // core::gain<NV>
		auto& wet_path3 = this->getT(5).getT(2).getT(1).getT(1);              // Band_impl::wet_path3_t<NV>
		auto& Tape3 = this->getT(5).getT(2).getT(1).getT(1).getT(0);          // project::Tape<NV>
		auto& IronOxide6 = this->getT(5).getT(2).getT(1).getT(1).getT(1);     // project::IronOxide5<NV>
		auto& Flutter1 = this->getT(5).getT(2).getT(1).getT(1).getT(2);       // project::Flutter<NV>
		auto& wet_gain3 = this->getT(5).getT(2).getT(1).getT(1).getT(3);      // core::gain<NV>
		auto& Sweeten1 = this->getT(5).getT(2).getT(2);                       // project::Sweeten<NV>
		auto& ClipSoftly1 = this->getT(5).getT(2).getT(3);                    // project::ClipSoftly<NV>
		
		// Parameter Connections -------------------------------------------------------------------
		
		TapeDryWet2.getParameterT(0).connectT(0, dry_wet_mixer4); // DryWet -> dry_wet_mixer4::Value
		TapeDryWet.getParameterT(0).connectT(0, dry_wet_mixer2);  // DryWet -> dry_wet_mixer2::Value
		TapeDryWet1.getParameterT(0).connectT(0, dry_wet_mixer3); // DryWet -> dry_wet_mixer3::Value
		this->getParameterT(0).connectT(0, Tubesmoother);         // Tube -> Tubesmoother::Value
		
		auto& Tape_p = this->getParameterT(1);
		Tape_p.connectT(0, TapeDryWet);  // Tape -> TapeDryWet::DryWet
		Tape_p.connectT(1, TapeDryWet2); // Tape -> TapeDryWet2::DryWet
		Tape_p.connectT(2, TapeDryWet1); // Tape -> TapeDryWet1::DryWet
		
		this->getParameterT(2).connectT(0, TapeSmootherSlam); // Tape_Slam -> TapeSmootherSlam::Value
		
		auto& Tape_high_p = this->getParameterT(3);
		Tape_high_p.connectT(0, IronOxide5); // Tape_high -> IronOxide5::TapeHigh
		Tape_high_p.connectT(1, IronOxide7); // Tape_high -> IronOxide7::TapeHigh
		Tape_high_p.connectT(2, IronOxide6); // Tape_high -> IronOxide6::TapeHigh
		
		this->getParameterT(4).connectT(0, low_invert); // Tape_low -> low_invert::Value
		
		auto& Flutter_p = this->getParameterT(5);
		Flutter_p.connectT(0, IronOxide5); // Flutter -> IronOxide5::Flutter
		Flutter_p.connectT(1, IronOxide7); // Flutter -> IronOxide7::Flutter
		Flutter_p.connectT(2, IronOxide6); // Flutter -> IronOxide6::Flutter
		Flutter_p.connectT(3, Flutter2);   // Flutter -> Flutter2::Flutter
		Flutter_p.connectT(4, Flutter);    // Flutter -> Flutter::Flutter
		Flutter_p.connectT(5, Flutter1);   // Flutter -> Flutter1::Flutter
		
		auto& Tape_noise_p = this->getParameterT(6);
		Tape_noise_p.connectT(0, IronOxide5); // Tape_noise -> IronOxide5::Noise
		Tape_noise_p.connectT(1, IronOxide7); // Tape_noise -> IronOxide7::Noise
		Tape_noise_p.connectT(2, IronOxide6); // Tape_noise -> IronOxide6::Noise
		
		auto& Tape_Sweeten_p = this->getParameterT(7);
		Tape_Sweeten_p.connectT(0, Sweeten);  // Tape_Sweeten -> Sweeten::Sweeten
		Tape_Sweeten_p.connectT(1, Sweeten2); // Tape_Sweeten -> Sweeten2::Sweeten
		Tape_Sweeten_p.connectT(2, Sweeten1); // Tape_Sweeten -> Sweeten1::Sweeten
		
		this->getParameterT(8).connectT(0, minmax1); // Hot -> minmax1::Value
		
		this->getParameterT(9).connectT(0, branch); // oversample -> branch::Index
		
		// Modulation Connections ------------------------------------------------------------------
		
		tubeinputminmax.getWrappedObject().getParameter().connectT(0, Tube2); // tubeinputminmax -> Tube2::Input
		tubeinputminmax.getWrappedObject().getParameter().connectT(1, Tube3); // tubeinputminmax -> Tube3::Input
		tubeinputminmax.getWrappedObject().getParameter().connectT(2, Tube4); // tubeinputminmax -> Tube4::Input
		tubeinputminmax.getWrappedObject().getParameter().connectT(3, Tube5); // tubeinputminmax -> Tube5::Input
		tubeinputminmax.getWrappedObject().getParameter().connectT(4, Tube6); // tubeinputminmax -> Tube6::Input
		tubeinputminmax.getWrappedObject().getParameter().connectT(5, Tube7); // tubeinputminmax -> Tube7::Input
		Tubesmoother.getParameter().connectT(0, Tube2);                       // Tubesmoother -> Tube2::Tube
		Tubesmoother.getParameter().connectT(1, Tube3);                       // Tubesmoother -> Tube3::Tube
		Tubesmoother.getParameter().connectT(2, Tube6);                       // Tubesmoother -> Tube6::Tube
		Tubesmoother.getParameter().connectT(3, Tube7);                       // Tubesmoother -> Tube7::Tube
		Tubesmoother.getParameter().connectT(4, tubeinputminmax);             // Tubesmoother -> tubeinputminmax::Value
		Tubesmoother.getParameter().connectT(5, Tube4);                       // Tubesmoother -> Tube4::Tube
		Tubesmoother.getParameter().connectT(6, Tube5);                       // Tubesmoother -> Tube5::Tube
		TapeSmootherSlam.getParameter().connectT(0, Tape2);                   // TapeSmootherSlam -> Tape2::Slam
		TapeSmootherSlam.getParameter().connectT(1, Tape4);                   // TapeSmootherSlam -> Tape4::Slam
		TapeSmootherSlam.getParameter().connectT(2, Tape3);                   // TapeSmootherSlam -> Tape3::Slam
		minmax1.getWrappedObject().getParameter().connectT(0, gain);          // minmax1 -> gain::Gain
		low_invert.getWrappedObject().getParameter().connectT(0, IronOxide5); // low_invert -> IronOxide5::TapeLow
		low_invert.getWrappedObject().getParameter().connectT(1, IronOxide7); // low_invert -> IronOxide7::TapeLow
		low_invert.getWrappedObject().getParameter().connectT(2, IronOxide6); // low_invert -> IronOxide6::TapeLow
		auto& dry_wet_mixer4_p = dry_wet_mixer4.getWrappedObject().getParameter();
		dry_wet_mixer4_p.getParameterT(0).connectT(0, dry_gain4); // dry_wet_mixer4 -> dry_gain4::Gain
		dry_wet_mixer4_p.getParameterT(1).connectT(0, wet_gain4); // dry_wet_mixer4 -> wet_gain4::Gain
		auto& dry_wet_mixer2_p = dry_wet_mixer2.getWrappedObject().getParameter();
		dry_wet_mixer2_p.getParameterT(0).connectT(0, dry_gain2); // dry_wet_mixer2 -> dry_gain2::Gain
		dry_wet_mixer2_p.getParameterT(1).connectT(0, wet_gain2); // dry_wet_mixer2 -> wet_gain2::Gain
		auto& dry_wet_mixer3_p = dry_wet_mixer3.getWrappedObject().getParameter();
		dry_wet_mixer3_p.getParameterT(0).connectT(0, dry_gain3); // dry_wet_mixer3 -> dry_gain3::Gain
		dry_wet_mixer3_p.getParameterT(1).connectT(0, wet_gain3); // dry_wet_mixer3 -> wet_gain3::Gain
		
		// Default Values --------------------------------------------------------------------------
		
		;                                    // Tubesmoother::Value is automated
		Tubesmoother.setParameterT(1, 100.); // control::smoothed_parameter::SmoothingTime
		Tubesmoother.setParameterT(2, 1.);   // control::smoothed_parameter::Enabled
		
		;                                        // TapeSmootherSlam::Value is automated
		TapeSmootherSlam.setParameterT(1, 100.); // control::smoothed_parameter::SmoothingTime
		TapeSmootherSlam.setParameterT(2, 1.);   // control::smoothed_parameter::Enabled
		
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
		tubeinputminmax.setParameterT(1, 0.5);      // control::minmax::Minimum
		tubeinputminmax.setParameterT(2, 0.85);     // control::minmax::Maximum
		tubeinputminmax.setParameterT(3, 0.210557); // control::minmax::Skew
		tubeinputminmax.setParameterT(4, 0.);       // control::minmax::Step
		tubeinputminmax.setParameterT(5, 0.);       // control::minmax::Polarity
		
		;                                 // low_invert::Value is automated
		low_invert.setParameterT(1, -1.); // control::pma::Multiply
		low_invert.setParameterT(2, 1.);  // control::pma::Add
		
		; // branch::Index is automated
		
		; // Tube6::Input is automated
		; // Tube6::Tube is automated
		
		; // Tube7::Input is automated
		; // Tube7::Tube is automated
		
		; // TapeDryWet2::DryWet is automated
		
		; // dry_wet_mixer4::Value is automated
		
		;                                // dry_gain4::Gain is automated
		dry_gain4.setParameterT(1, 20.); // core::gain::Smoothing
		dry_gain4.setParameterT(2, 0.);  // core::gain::ResetValue
		
		;                            // Tape4::Slam is automated
		Tape4.setParameterT(1, 0.5); // project::Tape::Bump
		
		IronOxide7.setParameterT(0, 0.5); // project::IronOxide5::InputTrim
		;                                 // IronOxide7::TapeHigh is automated
		;                                 // IronOxide7::TapeLow is automated
		;                                 // IronOxide7::Flutter is automated
		;                                 // IronOxide7::Noise is automated
		IronOxide7.setParameterT(5, 0.5); // project::IronOxide5::OutputTrim
		IronOxide7.setParameterT(6, 1.);  // project::IronOxide5::InvDryWet
		
		; // Flutter2::Flutter is automated
		
		;                                // wet_gain4::Gain is automated
		wet_gain4.setParameterT(1, 20.); // core::gain::Smoothing
		wet_gain4.setParameterT(2, 0.);  // core::gain::ResetValue
		
		; // Sweeten2::Sweeten is automated
		
		; // Tube2::Input is automated
		; // Tube2::Tube is automated
		
		; // Tube3::Input is automated
		; // Tube3::Tube is automated
		
		; // TapeDryWet::DryWet is automated
		
		; // dry_wet_mixer2::Value is automated
		
		;                                // dry_gain2::Gain is automated
		dry_gain2.setParameterT(1, 20.); // core::gain::Smoothing
		dry_gain2.setParameterT(2, 0.);  // core::gain::ResetValue
		
		;                            // Tape2::Slam is automated
		Tape2.setParameterT(1, 0.5); // project::Tape::Bump
		
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
		
		; // Tube4::Input is automated
		; // Tube4::Tube is automated
		
		; // Tube5::Input is automated
		; // Tube5::Tube is automated
		
		; // TapeDryWet1::DryWet is automated
		
		; // dry_wet_mixer3::Value is automated
		
		;                                // dry_gain3::Gain is automated
		dry_gain3.setParameterT(1, 20.); // core::gain::Smoothing
		dry_gain3.setParameterT(2, 0.);  // core::gain::ResetValue
		
		;                            // Tape3::Slam is automated
		Tape3.setParameterT(1, 0.5); // project::Tape::Bump
		
		IronOxide6.setParameterT(0, 0.5); // project::IronOxide5::InputTrim
		;                                 // IronOxide6::TapeHigh is automated
		;                                 // IronOxide6::TapeLow is automated
		;                                 // IronOxide6::Flutter is automated
		;                                 // IronOxide6::Noise is automated
		IronOxide6.setParameterT(5, 0.5); // project::IronOxide5::OutputTrim
		IronOxide6.setParameterT(6, 1.);  // project::IronOxide5::InvDryWet
		
		; // Flutter1::Flutter is automated
		
		;                                // wet_gain3::Gain is automated
		wet_gain3.setParameterT(1, 20.); // core::gain::Smoothing
		wet_gain3.setParameterT(2, 0.);  // core::gain::ResetValue
		
		; // Sweeten1::Sweeten is automated
		
		this->setParameterT(0, 0.);
		this->setParameterT(1, 0.710111);
		this->setParameterT(2, 0.365859);
		this->setParameterT(3, 0.501248);
		this->setParameterT(4, 0.806842);
		this->setParameterT(5, 0.134729);
		this->setParameterT(6, 0.90483);
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


