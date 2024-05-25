#pragma once

#include "Tube2.h"
#include "ToTape5.h"
#include "ToVinyl4.h"
#include "Pockey2.h"
#include "TexturizeMS.h"
#include "TapeDust.h"
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
using branch_t = container::branch<parameter::empty, 
                                   wrap::fix<2, project::ToTape5<NV>>, 
                                   project::ToVinyl4<NV>, 
                                   project::Pockey2<NV>>;

template <int NV> using dry_wet_mixer1_c0 = dry_wet_mixer_c0<NV>;

template <int NV> using dry_wet_mixer1_c1 = dry_wet_mixer_c0<NV>;

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
using branch1_t = container::branch<parameter::empty, 
                                    wrap::fix<2, project::TexturizeMS<NV>>, 
                                    project::TapeDust<NV>>;

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

template <int NV>
using wet_path_t = container::chain<parameter::empty, 
                                    wrap::fix<2, core::gain<NV>>, 
                                    project::Tube2<NV>, 
                                    branch_t<NV>, 
                                    dry_wet2_t<NV>, 
                                    core::gain<NV>>;

namespace dry_wet1_t_parameters
{
}

template <int NV>
using dry_wet1_t = container::split<parameter::plain<Band_impl::dry_wet_mixer_t<NV>, 0>, 
                                    wrap::fix<2, dry_path_t<NV>>, 
                                    wet_path_t<NV>>;

namespace Band_t_parameters
{
// Parameter list for Band_impl::Band_t ------------------------------------------------------------

template <int NV>
using InputGain = parameter::plain<core::gain<NV>, 0>;
template <int NV>
using Tube = parameter::plain<project::Tube2<NV>, 1>;
template <int NV>
using DeFreq = parameter::plain<project::Pockey2<NV>, 0>;
template <int NV>
using DeRez = parameter::plain<project::Pockey2<NV>, 1>;
template <int NV>
using PockeyMix = parameter::plain<project::Pockey2<NV>, 2>;
template <int NV>
using Mode = parameter::plain<Band_impl::branch_t<NV>, 
                              0>;
template <int NV>
using Louder = parameter::plain<project::ToTape5<NV>, 0>;
template <int NV>
using Softer = parameter::plain<project::ToTape5<NV>, 1>;
template <int NV>
using Fatter = parameter::plain<project::ToTape5<NV>, 2>;
template <int NV>
using Flutter = parameter::plain<project::ToTape5<NV>, 3>;
template <int NV>
using Output = parameter::plain<project::ToTape5<NV>, 4>;
template <int NV>
using TapeMix = parameter::plain<project::ToTape5<NV>, 5>;
template <int NV>
using MidHiP = parameter::plain<project::ToVinyl4<NV>, 0>;
template <int NV>
using SideHiP = parameter::plain<project::ToVinyl4<NV>, 1>;
template <int NV>
using HLimit = parameter::plain<project::ToVinyl4<NV>, 2>;
template <int NV>
using VinylWear = parameter::plain<project::ToVinyl4<NV>, 3>;
template <int NV>
using Mix = parameter::plain<Band_impl::dry_wet1_t<NV>, 
                             0>;
template <int NV>
using TubeInput = parameter::plain<project::Tube2<NV>, 0>;
template <int NV>
using TextureMode = parameter::plain<Band_impl::branch1_t<NV>, 
                                     0>;
template <int NV>
using BrightM = parameter::plain<project::TexturizeMS<NV>, 
                                 0>;
template <int NV>
using PunchyM = parameter::plain<project::TexturizeMS<NV>, 
                                 1>;
template <int NV>
using DryWetM = parameter::plain<project::TexturizeMS<NV>, 
                                 2>;
template <int NV>
using BrightS = parameter::plain<project::TexturizeMS<NV>, 
                                 3>;
template <int NV>
using PunchyS = parameter::plain<project::TexturizeMS<NV>, 
                                 4>;
template <int NV>
using DryWetS = parameter::plain<project::TexturizeMS<NV>, 
                                 5>;
template <int NV>
using Dust = parameter::plain<project::TapeDust<NV>, 0>;
template <int NV>
using Dust_DryWet = parameter::plain<project::TapeDust<NV>, 1>;
template <int NV>
using TextureMix = parameter::plain<Band_impl::dry_wet2_t<NV>, 
                                    0>;
template <int NV>
using Band_t_plist = parameter::list<InputGain<NV>, 
                                     Tube<NV>, 
                                     DeFreq<NV>, 
                                     DeRez<NV>, 
                                     PockeyMix<NV>, 
                                     Mode<NV>, 
                                     Louder<NV>, 
                                     Softer<NV>, 
                                     Fatter<NV>, 
                                     Flutter<NV>, 
                                     Output<NV>, 
                                     TapeMix<NV>, 
                                     MidHiP<NV>, 
                                     SideHiP<NV>, 
                                     HLimit<NV>, 
                                     VinylWear<NV>, 
                                     Mix<NV>, 
                                     TubeInput<NV>, 
                                     TextureMode<NV>, 
                                     BrightM<NV>, 
                                     PunchyM<NV>, 
                                     DryWetM<NV>, 
                                     BrightS<NV>, 
                                     PunchyS<NV>, 
                                     DryWetS<NV>, 
                                     Dust<NV>, 
                                     Dust_DryWet<NV>, 
                                     TextureMix<NV>>;
}

template <int NV>
using Band_t_ = container::chain<Band_t_parameters::Band_t_plist<NV>, 
                                 wrap::fix<2, dry_wet1_t<NV>>, 
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
		SNEX_METADATA_ENCODED_PARAMETERS(462)
		{
			0x005B, 0x0000, 0x4900, 0x706E, 0x7475, 0x6147, 0x6E69, 0x0000, 
            0x7000, 0x00C2, 0x4000, 0xF041, 0xFDA7, 0x3E3E, 0xAD83, 0xCD40, 
            0xCCCC, 0x5B3D, 0x0001, 0x0000, 0x7554, 0x6562, 0x0000, 0x0000, 
            0x0000, 0x8000, 0xC53F, 0xFF20, 0x003E, 0x8000, 0x003F, 0x0000, 
            0x5B00, 0x0002, 0x0000, 0x6544, 0x7246, 0x7165, 0x0000, 0x0000, 
            0x0000, 0x8000, 0x003F, 0x0000, 0x0000, 0x8000, 0x003F, 0x0000, 
            0x5B00, 0x0003, 0x0000, 0x6544, 0x6552, 0x007A, 0x0000, 0x0000, 
            0x0000, 0x3F80, 0x0000, 0x0000, 0x0000, 0x3F80, 0x0000, 0x0000, 
            0x045B, 0x0000, 0x5000, 0x636F, 0x656B, 0x4D79, 0x7869, 0x0000, 
            0x0000, 0x0000, 0x8000, 0x003F, 0x8000, 0x003F, 0x8000, 0x003F, 
            0x0000, 0x5B00, 0x0005, 0x0000, 0x6F4D, 0x6564, 0x0000, 0x0000, 
            0x0000, 0x0000, 0x0040, 0x8000, 0x003F, 0x8000, 0x003F, 0x8000, 
            0x5B3F, 0x0006, 0x0000, 0x6F4C, 0x6475, 0x7265, 0x0000, 0x0000, 
            0x0000, 0x8000, 0xC73F, 0x3FEB, 0x003E, 0x8000, 0x003F, 0x0000, 
            0x5B00, 0x0007, 0x0000, 0x6F53, 0x7466, 0x7265, 0x0000, 0x0000, 
            0x0000, 0x8000, 0xB63F, 0x9EA2, 0x003E, 0x8000, 0x003F, 0x0000, 
            0x5B00, 0x0008, 0x0000, 0x6146, 0x7474, 0x7265, 0x0000, 0x0000, 
            0x0000, 0x8000, 0x193F, 0x07AE, 0x003E, 0x8000, 0x003F, 0x0000, 
            0x5B00, 0x0009, 0x0000, 0x6C46, 0x7475, 0x6574, 0x0072, 0x0000, 
            0x0000, 0x0000, 0x3F80, 0xB021, 0x3DE6, 0x0000, 0x3F80, 0x0000, 
            0x0000, 0x0A5B, 0x0000, 0x4F00, 0x7475, 0x7570, 0x0074, 0x0000, 
            0x0000, 0x0000, 0x3F80, 0x87FB, 0x3F01, 0x0000, 0x3F80, 0x0000, 
            0x0000, 0x0B5B, 0x0000, 0x5400, 0x7061, 0x4D65, 0x7869, 0x0000, 
            0x0000, 0x0000, 0x8000, 0x003F, 0x8000, 0x003F, 0x8000, 0x003F, 
            0x0000, 0x5B00, 0x000C, 0x0000, 0x694D, 0x4864, 0x5069, 0x0000, 
            0x0000, 0x0000, 0x8000, 0xEC3F, 0xDFB5, 0x003E, 0x8000, 0x003F, 
            0x0000, 0x5B00, 0x000D, 0x0000, 0x6953, 0x6564, 0x6948, 0x0050, 
            0x0000, 0x0000, 0x0000, 0x3F80, 0xDD3B, 0x3E4F, 0x0000, 0x3F80, 
            0x0000, 0x0000, 0x0E5B, 0x0000, 0x4800, 0x694C, 0x696D, 0x0074, 
            0x0000, 0x0000, 0x0000, 0x3F80, 0xFAF0, 0x3F4A, 0x0000, 0x3F80, 
            0x0000, 0x0000, 0x0F5B, 0x0000, 0x5600, 0x6E69, 0x6C79, 0x6557, 
            0x7261, 0x0000, 0x0000, 0x0000, 0x8000, 0x833F, 0xB2FC, 0x003D, 
            0x8000, 0x003F, 0x0000, 0x5B00, 0x0010, 0x0000, 0x694D, 0x0078, 
            0x0000, 0x0000, 0x0000, 0x3F80, 0x0000, 0x3F80, 0x0000, 0x3F80, 
            0x0000, 0x0000, 0x115B, 0x0000, 0x5400, 0x6275, 0x4965, 0x706E, 
            0x7475, 0x0000, 0x0000, 0x0000, 0x8000, 0x3F3F, 0x0097, 0x003F, 
            0x8000, 0x003F, 0x0000, 0x5B00, 0x0012, 0x0000, 0x6554, 0x7478, 
            0x7275, 0x4D65, 0x646F, 0x0065, 0x0000, 0x0000, 0x0000, 0x3F80, 
            0x0000, 0x3F80, 0x0000, 0x3F80, 0x0000, 0x3F80, 0x135B, 0x0000, 
            0x4200, 0x6972, 0x6867, 0x4D74, 0x0000, 0x0000, 0x0000, 0x8000, 
            0xA63F, 0x00C5, 0x003F, 0x8000, 0x003F, 0x0000, 0x5B00, 0x0014, 
            0x0000, 0x7550, 0x636E, 0x7968, 0x004D, 0x0000, 0x0000, 0x0000, 
            0x3F80, 0x8964, 0x3F02, 0x0000, 0x3F80, 0x0000, 0x0000, 0x155B, 
            0x0000, 0x4400, 0x7972, 0x6557, 0x4D74, 0x0000, 0x0000, 0x0000, 
            0x8000, 0x393F, 0xF61E, 0x003E, 0x8000, 0x003F, 0x0000, 0x5B00, 
            0x0016, 0x0000, 0x7242, 0x6769, 0x7468, 0x0053, 0x0000, 0x0000, 
            0x0000, 0x3F80, 0x3F58, 0x3F01, 0x0000, 0x3F80, 0x0000, 0x0000, 
            0x175B, 0x0000, 0x5000, 0x6E75, 0x6863, 0x5379, 0x0000, 0x0000, 
            0x0000, 0x8000, 0xBC3F, 0xF2DC, 0x003E, 0x8000, 0x003F, 0x0000, 
            0x5B00, 0x0018, 0x0000, 0x7244, 0x5779, 0x7465, 0x0053, 0x0000, 
            0x0000, 0x0000, 0x3F80, 0x4C5C, 0x3F08, 0x0000, 0x3F80, 0x0000, 
            0x0000, 0x195B, 0x0000, 0x4400, 0x7375, 0x0074, 0x0000, 0x0000, 
            0x0000, 0x3F80, 0x0000, 0x0000, 0x0000, 0x3F80, 0x0000, 0x0000, 
            0x1A5B, 0x0000, 0x4400, 0x7375, 0x5F74, 0x7244, 0x5779, 0x7465, 
            0x0000, 0x0000, 0x0000, 0x8000, 0x003F, 0x8000, 0x003F, 0x8000, 
            0x003F, 0x0000, 0x5B00, 0x001B, 0x0000, 0x6554, 0x7478, 0x7275, 
            0x4D65, 0x7869, 0x0000, 0x0000, 0x0000, 0x8000, 0x003F, 0x8000, 
            0x003F, 0x8000, 0x003F, 0x0000, 0x0000, 0x0000
		};
	};
	
	instance()
	{
		// Node References -------------------------------------------------------------------------
		
		auto& dry_wet1 = this->getT(0);                                            // Band_impl::dry_wet1_t<NV>
		auto& dry_path = this->getT(0).getT(0);                                    // Band_impl::dry_path_t<NV>
		auto& dry_wet_mixer = this->getT(0).getT(0).getT(0);                       // Band_impl::dry_wet_mixer_t<NV>
		auto& dry_gain = this->getT(0).getT(0).getT(1);                            // core::gain<NV>
		auto& wet_path = this->getT(0).getT(1);                                    // Band_impl::wet_path_t<NV>
		auto& gain1 = this->getT(0).getT(1).getT(0);                               // core::gain<NV>
		auto& Tube2 = this->getT(0).getT(1).getT(1);                               // project::Tube2<NV>
		auto& branch = this->getT(0).getT(1).getT(2);                              // Band_impl::branch_t<NV>
		auto& ToTape5 = this->getT(0).getT(1).getT(2).getT(0);                     // project::ToTape5<NV>
		auto& ToVinyl4 = this->getT(0).getT(1).getT(2).getT(1);                    // project::ToVinyl4<NV>
		auto& Pockey2 = this->getT(0).getT(1).getT(2).getT(2);                     // project::Pockey2<NV>
		auto& dry_wet2 = this->getT(0).getT(1).getT(3);                            // Band_impl::dry_wet2_t<NV>
		auto& dry_path1 = this->getT(0).getT(1).getT(3).getT(0);                   // Band_impl::dry_path1_t<NV>
		auto& dry_wet_mixer1 = this->getT(0).getT(1).getT(3).getT(0).getT(0);      // Band_impl::dry_wet_mixer1_t<NV>
		auto& dry_gain1 = this->getT(0).getT(1).getT(3).getT(0).getT(1);           // core::gain<NV>
		auto& wet_path1 = this->getT(0).getT(1).getT(3).getT(1);                   // Band_impl::wet_path1_t<NV>
		auto& branch1 = this->getT(0).getT(1).getT(3).getT(1).getT(0);             // Band_impl::branch1_t<NV>
		auto& TexturizeMS = this->getT(0).getT(1).getT(3).getT(1).getT(0).getT(0); // project::TexturizeMS<NV>
		auto& TapeDust = this->getT(0).getT(1).getT(3).getT(1).getT(0).getT(1);    // project::TapeDust<NV>
		auto& wet_gain1 = this->getT(0).getT(1).getT(3).getT(1).getT(1);           // core::gain<NV>
		auto& wet_gain = this->getT(0).getT(1).getT(4);                            // core::gain<NV>
		auto& ClipSoftly = this->getT(1);                                          // project::ClipSoftly<NV>
		
		// Parameter Connections -------------------------------------------------------------------
		
		dry_wet2.getParameterT(0).connectT(0, dry_wet_mixer1); // DryWet -> dry_wet_mixer1::Value
		dry_wet1.getParameterT(0).connectT(0, dry_wet_mixer);  // DryWet -> dry_wet_mixer::Value
		this->getParameterT(0).connectT(0, gain1);             // InputGain -> gain1::Gain
		
		this->getParameterT(1).connectT(0, Tube2); // Tube -> Tube2::Tube
		
		this->getParameterT(2).connectT(0, Pockey2); // DeFreq -> Pockey2::DeFreq
		
		this->getParameterT(3).connectT(0, Pockey2); // DeRez -> Pockey2::DeRez
		
		this->getParameterT(4).connectT(0, Pockey2); // PockeyMix -> Pockey2::DryWet
		
		this->getParameterT(5).connectT(0, branch); // Mode -> branch::Index
		
		this->getParameterT(6).connectT(0, ToTape5); // Louder -> ToTape5::Louder
		
		this->getParameterT(7).connectT(0, ToTape5); // Softer -> ToTape5::Softer
		
		this->getParameterT(8).connectT(0, ToTape5); // Fatter -> ToTape5::Fatter
		
		this->getParameterT(9).connectT(0, ToTape5); // Flutter -> ToTape5::Flutter
		
		this->getParameterT(10).connectT(0, ToTape5); // Output -> ToTape5::Output
		
		this->getParameterT(11).connectT(0, ToTape5); // TapeMix -> ToTape5::DryWet
		
		this->getParameterT(12).connectT(0, ToVinyl4); // MidHiP -> ToVinyl4::MidHiP
		
		this->getParameterT(13).connectT(0, ToVinyl4); // SideHiP -> ToVinyl4::SideHiP
		
		this->getParameterT(14).connectT(0, ToVinyl4); // HLimit -> ToVinyl4::HLimit
		
		this->getParameterT(15).connectT(0, ToVinyl4); // VinylWear -> ToVinyl4::GvWear
		
		this->getParameterT(16).connectT(0, dry_wet1); // Mix -> dry_wet1::DryWet
		
		this->getParameterT(17).connectT(0, Tube2); // TubeInput -> Tube2::Input
		
		this->getParameterT(18).connectT(0, branch1); // TextureMode -> branch1::Index
		
		this->getParameterT(19).connectT(0, TexturizeMS); // BrightM -> TexturizeMS::BrightM
		
		this->getParameterT(20).connectT(0, TexturizeMS); // PunchyM -> TexturizeMS::PunchyM
		
		this->getParameterT(21).connectT(0, TexturizeMS); // DryWetM -> TexturizeMS::DryWetM
		
		this->getParameterT(22).connectT(0, TexturizeMS); // BrightS -> TexturizeMS::BrightS
		
		this->getParameterT(23).connectT(0, TexturizeMS); // PunchyS -> TexturizeMS::PunchyS
		
		this->getParameterT(24).connectT(0, TexturizeMS); // DryWetS -> TexturizeMS::DryWetS
		
		this->getParameterT(25).connectT(0, TapeDust); // Dust -> TapeDust::Dust
		
		this->getParameterT(26).connectT(0, TapeDust); // Dust_DryWet -> TapeDust::DryWet
		
		this->getParameterT(27).connectT(0, dry_wet2); // TextureMix -> dry_wet2::DryWet
		
		// Modulation Connections ------------------------------------------------------------------
		
		auto& dry_wet_mixer_p = dry_wet_mixer.getWrappedObject().getParameter();
		dry_wet_mixer_p.getParameterT(0).connectT(0, dry_gain); // dry_wet_mixer -> dry_gain::Gain
		dry_wet_mixer_p.getParameterT(1).connectT(0, wet_gain); // dry_wet_mixer -> wet_gain::Gain
		auto& dry_wet_mixer1_p = dry_wet_mixer1.getWrappedObject().getParameter();
		dry_wet_mixer1_p.getParameterT(0).connectT(0, dry_gain1); // dry_wet_mixer1 -> dry_gain1::Gain
		dry_wet_mixer1_p.getParameterT(1).connectT(0, wet_gain1); // dry_wet_mixer1 -> wet_gain1::Gain
		
		// Default Values --------------------------------------------------------------------------
		
		; // dry_wet1::DryWet is automated
		
		; // dry_wet_mixer::Value is automated
		
		;                               // dry_gain::Gain is automated
		dry_gain.setParameterT(1, 20.); // core::gain::Smoothing
		dry_gain.setParameterT(2, 0.);  // core::gain::ResetValue
		
		;                            // gain1::Gain is automated
		gain1.setParameterT(1, 20.); // core::gain::Smoothing
		gain1.setParameterT(2, 0.);  // core::gain::ResetValue
		
		; // Tube2::Input is automated
		; // Tube2::Tube is automated
		
		; // branch::Index is automated
		
		; // ToTape5::Louder is automated
		; // ToTape5::Softer is automated
		; // ToTape5::Fatter is automated
		; // ToTape5::Flutter is automated
		; // ToTape5::Output is automated
		; // ToTape5::DryWet is automated
		
		; // ToVinyl4::MidHiP is automated
		; // ToVinyl4::SideHiP is automated
		; // ToVinyl4::HLimit is automated
		; // ToVinyl4::GvWear is automated
		
		; // Pockey2::DeFreq is automated
		; // Pockey2::DeRez is automated
		; // Pockey2::DryWet is automated
		
		; // dry_wet2::DryWet is automated
		
		; // dry_wet_mixer1::Value is automated
		
		;                                // dry_gain1::Gain is automated
		dry_gain1.setParameterT(1, 20.); // core::gain::Smoothing
		dry_gain1.setParameterT(2, 0.);  // core::gain::ResetValue
		
		; // branch1::Index is automated
		
		; // TexturizeMS::BrightM is automated
		; // TexturizeMS::PunchyM is automated
		; // TexturizeMS::DryWetM is automated
		; // TexturizeMS::BrightS is automated
		; // TexturizeMS::PunchyS is automated
		; // TexturizeMS::DryWetS is automated
		
		; // TapeDust::Dust is automated
		; // TapeDust::DryWet is automated
		
		;                                // wet_gain1::Gain is automated
		wet_gain1.setParameterT(1, 20.); // core::gain::Smoothing
		wet_gain1.setParameterT(2, 0.);  // core::gain::ResetValue
		
		;                               // wet_gain::Gain is automated
		wet_gain.setParameterT(1, 20.); // core::gain::Smoothing
		wet_gain.setParameterT(2, 0.);  // core::gain::ResetValue
		
		this->setParameterT(0, 0.495422);
		this->setParameterT(1, 0.498297);
		this->setParameterT(2, 0.);
		this->setParameterT(3, 0.);
		this->setParameterT(4, 1.);
		this->setParameterT(5, 1.);
		this->setParameterT(6, 0.187423);
		this->setParameterT(7, 0.309835);
		this->setParameterT(8, 0.1325);
		this->setParameterT(9, 0.112641);
		this->setParameterT(10, 0.505981);
		this->setParameterT(11, 1.);
		this->setParameterT(12, 0.436935);
		this->setParameterT(13, 0.202992);
		this->setParameterT(14, 0.792891);
		this->setParameterT(15, 0.0873957);
		this->setParameterT(16, 1.);
		this->setParameterT(17, 0.502308);
		this->setParameterT(18, 1.);
		this->setParameterT(19, 0.503016);
		this->setParameterT(20, 0.509909);
		this->setParameterT(21, 0.480699);
		this->setParameterT(22, 0.504873);
		this->setParameterT(23, 0.47434);
		this->setParameterT(24, 0.532415);
		this->setParameterT(25, 0.);
		this->setParameterT(26, 1.);
		this->setParameterT(27, 1.);
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


