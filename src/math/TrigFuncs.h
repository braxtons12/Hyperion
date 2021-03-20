#pragma once

#include "../utils/Concepts.h"
#include "Constants.h"
#include "General.h"

namespace math {

	using utils::concepts::FloatingPoint;

	/// @brief Collection of approximations of various Trigonometric functions
	class Trig {
	  public:
		/// @brief Fast approximation calculation of cosine(angle)
		///
		/// @param angle - The angle to calculate the cosine of
		/// @return - The cosine of the angle
		[[nodiscard]] static constexpr inline auto
		cos(FloatingPoint auto angle) noexcept -> decltype(angle) {
			if constexpr(std::is_same_v<decltype(angle), float>) {
				return cosf_internal(angle);
			}
			else {
				return cos_internal(angle);
			}
		}

		/// @brief Fast approximation calculation of sine(angle)
		///
		/// @param angle - The angle to calculate the sine of
		/// @return - The sine of the angle
		[[nodiscard]] static constexpr inline auto
		sin(FloatingPoint auto angle) noexcept -> decltype(angle) {
			if constexpr(std::is_same_v<decltype(angle), float>) {
				return sinf_internal(angle);
			}
			else {
				return sin_internal(angle);
			}
		}

		/// @brief Fast approximation calculation of tangent(angle)
		///
		/// @param angle - The angle to calculate the tangent of
		/// @return - The tangent of the angle
		[[nodiscard]] static constexpr inline auto
		tan(FloatingPoint auto angle) noexcept -> decltype(auto) {
			if constexpr(std::is_same_v<decltype(angle), float>) {
				return tanf_internal(angle);
			}
			else {
				return tan_internal(angle);
			}
		}

		/// @brief Fast approximation calculation of arctangent(angle)
		///
		/// @param angle - The angle to calculate the arctangent of
		/// @return - The arctangent of the angle
		[[nodiscard]] static constexpr inline auto
		atan(FloatingPoint auto angle) noexcept -> decltype(angle) {
			if constexpr(std::is_same_v<decltype(angle), float>) {
				return atanf_internal(angle);
			}
			else {
				return atan_internal(angle);
			}
		}

		/// @brief Fast approximation calculation of the hyperbolic tangent ("tanch") of the angle
		///
		/// @param angle - The angle to calculate the hyperbolic tanget of
		/// @return - The hyperbolic tangent of the angle
		[[nodiscard]] static constexpr inline auto
		tanh(FloatingPoint auto angle) noexcept -> decltype(angle) {
			if constexpr(std::is_same_v<decltype(angle), float>) {
				return tanhf_internal(angle);
			}
			else {
				return tanh_internal(angle);
			}
		}

	  private:
		/// @brief Helper function for `cosf`; Don't use on its own
		///
		/// @param x - the angle
		/// @return - cos(x)
		[[nodiscard]] static constexpr inline auto cos_helperf(float x) noexcept -> float {
			constexpr float c1 = 0.99999999999925182F;
			constexpr float c2 = -0.49999999997024012F;
			constexpr float c3 = 0.041666666473384543F;
			constexpr float c4 = -0.001388888418000423F;
			constexpr float c5 = 0.0000248010406484558F;
			constexpr float c6 = -0.0000002752469638432F;
			constexpr float c7 = 0.0000000019907856854F;

			const auto x2 = x * x; // The input argument squared

			return (c1 + x2 * (c2 + x2 * (c3 + x2 * (c4 + x2 * (c5 + x2 * (c6 + c7 * x2))))));
		}

		/// @brief Fast approximation calculation of cosine(angle)
		///
		/// @param angle - The angle to calculate the cosine of
		/// @return - The cosine of the angle
		[[nodiscard]] static constexpr inline auto cosf_internal(float angle) noexcept -> float {
			angle = General::fmod(angle, Constants<float>::twoPi); // Get rid of values > 2* pi
			if(angle < 0.0F) {
				angle = -angle; // cos(-x) = cos(x)
			}
			const auto quad = static_cast<int>(
				angle * Constants<float>::twoOverPi); // Get quadrant # (0 to 3) we're in
			switch(quad) {
				case 0: return cos_helperf(angle);
				case 1: return -cos_helperf(Constants<float>::pi - angle);
				case 2: return -cos_helperf(angle - Constants<float>::pi);
				case 3: return cos_helperf(Constants<float>::twoPi - angle);
				default: return 0.0F;
			}
		}

		/// @brief Fast approximation calculation of sine(angle)
		///
		/// @param angle - The angle to calculate the sine of
		/// @return - The sine of the angle
		[[nodiscard]] static constexpr inline auto sinf_internal(float angle) noexcept -> float {
			return cosf_internal(Constants<float>::piOver2 - angle);
		}

		/// @brief Helper function for `tanf`; Don't use on its own
		///
		/// @param x - the angle
		/// @return - tan(x)
		[[nodiscard]] static constexpr inline auto tan_helperf(float x) noexcept -> float {
			constexpr float c1 = -34287.4662577359568109624F;
			constexpr float c2 = 2566.7175462315050423295F;
			constexpr float c3 = -26.5366371951731325438F;
			constexpr float c4 = -43656.1579281292375769579F;
			constexpr float c5 = 12244.4839556747426927793F;
			constexpr float c6 = -336.611376245464339493F;

			const auto x2 = x * x; // The input argument squared

			return (x * (c1 + x2 * (c2 + x2 * c3)) / (c4 + x2 * (c5 + x2 * (c6 + x2))));
		}

		/// @brief Fast approximation calculation of tangent(angle)
		///
		/// @param angle - The angle to calculate the tangent of
		/// @return - The tangent of the angle
		[[nodiscard]] static constexpr inline auto tanf_internal(float angle) noexcept -> float {
			angle = General::fmod(angle, Constants<float>::twoPi); // Get rid of values >2 *pi
			const auto octant
				= static_cast<int>(angle / Constants<float>::fourOverPi); // Get octant # (0 to 7)
			switch(octant) {
				case 0: return tan_helperf(angle * Constants<float>::fourOverPi);
				case 1:
					return 1.0F
						   / tan_helperf((Constants<float>::piOver2 - angle)
										 * Constants<float>::fourOverPi);
				case 2:
					return -1.0F
						   / tan_helperf((angle - Constants<float>::piOver2)
										 * Constants<float>::fourOverPi);
				case 3:
					return -tan_helperf((Constants<float>::pi - angle)
										* Constants<float>::fourOverPi);
				case 4:
					return tan_helperf((angle - Constants<float>::pi)
									   * Constants<float>::fourOverPi);
				case 5:
					return 1.0F
						   / tan_helperf((Constants<float>::threePiOver2 - angle)
										 * Constants<float>::fourOverPi);
				case 6:
					return -1.0F
						   / tan_helperf((angle - Constants<float>::threePiOver2)
										 * Constants<float>::fourOverPi);
				case 7:
					return -tan_helperf((Constants<float>::twoPi - angle)
										* Constants<float>::fourOverPi);
				default: return 0.0F;
			}
		}

		/// @brief Helper function for `atanf`; Don't use on its own
		///
		/// @param x - the angle
		/// @return atan(x)
		[[nodiscard]] static constexpr inline auto atan_helperf(float x) noexcept -> float {
			constexpr float c1 = 48.70107004404898384F;
			constexpr float c2 = 49.5326263772254345F;
			constexpr float c3 = 9.40604244231624F;
			constexpr float c4 = 48.70107004404996166F;
			constexpr float c5 = 65.7663163908956299F;
			constexpr float c6 = 21.587934067020262F;

			const auto x2 = x * x; // The input argument squared

			return (x * (c1 + x2 * (c2 + x2 * c3)) / (c4 + x2 * (c5 + x2 * (c6 + x2))));
		}

		/// @brief Fast approximation calculation of arctangent(angle)
		///
		/// @param angle - The angle to calculate the arctangent of
		/// @return - The arctangent of the angle
		[[nodiscard]] static constexpr inline auto atanf_internal(float angle) noexcept -> float {
			constexpr const float tanPiOver12f = tanf_internal(Constants<float>::piOver12);
			constexpr const float tanPiOver6f = tanf_internal(Constants<float>::piOver6);
			bool complement = false; // true if arg was >1
			bool region = false;	 // true depending on region arg is in
			bool sign = false;		 // true if arg was < 0

			if(angle < 0.0F) {
				angle = -angle;
				sign = true; // arctan(-x)=-arctan(x)
			}
			if(angle > 1.0F) {
				angle = 1.0F / angle; // keep arg between 0 and 1
				complement = true;
			}
			if(angle > tanPiOver12f) {
				angle = (angle - tanPiOver6f)
						/ (1.0F + tanPiOver6f * angle); // reduce arg to under tan(pi/12)
				region = true;
			}

			float y = atan_helperf(angle); // run the approximation
			if(region) {
				y += Constants<float>::piOver6; // correct for region we're in
			}
			if(complement) {
				y = Constants<float>::piOver2 - y; // correct for 1/x if we did that
			}
			if(sign) {
				y = -y; // correct for negative arg
			}
			return y;
		}

		/// @brief Fast approximation calculation of the hyperbolic tangent ("tanch") of the angle
		///
		/// @param angle - The angle to calculate the hyperbolic tanget of
		/// @return - The hyperbolic tangent of the angle
		[[nodiscard]] static constexpr inline auto tanhf_internal(float angle) noexcept -> float {
			if(angle < 0.0F) {
				angle *= -1.0F;
				return -(-0.67436811832e-5F
						 + (0.2468149110712040F
							+ (0.0583691066395175F + 0.03357335044280075F * angle) * angle)
							   * angle)
					   / (0.2464845986383725F
						  + (0.0609347197060491F
							 + (0.1086202599228572F + 0.02874707922475963F * angle) * angle)
								* angle);
			}
			else {
				return (-0.67436811832e-5F
						+ (0.2468149110712040F
						   + (0.0583691066395175F + 0.03357335044280075F * angle) * angle)
							  * angle)
					   / (0.2464845986383725F
						  + (0.0609347197060491F
							 + (0.1086202599228572F + 0.02874707922475963F * angle) * angle)
								* angle);
			}
		}

		/// @brief Helper function for `cos`; Don't use on its own
		///
		/// @param x - The angle
		/// @return cos(x)
		[[nodiscard]] static constexpr inline auto cos_helper(double x) noexcept -> double {
			constexpr double c1 = 0.99999999999925182;
			constexpr double c2 = -0.49999999997024012;
			constexpr double c3 = 0.041666666473384543;
			constexpr double c4 = -0.001388888418000423;
			constexpr double c5 = 0.0000248010406484558;
			constexpr double c6 = -0.0000002752469638432;
			constexpr double c7 = 0.0000000019907856854;

			const double x2 = x * x; // The input argument squared

			return (c1 + x2 * (c2 + x2 * (c3 + x2 * (c4 + x2 * (c5 + x2 * (c6 + c7 * x2))))));
		}

		/// @brief Fast approximation calculation of cosine(angle)
		///
		/// @param angle - The angle to calculate the cosine of
		/// @return - The cosine of the angle
		[[nodiscard]] static constexpr inline auto cos_internal(double angle) noexcept -> double {
			angle = General::fmod(angle, Constants<double>::twoPi); // Get rid of values > 2* pi
			if(angle < 0.0) {
				angle = -angle; // cos(-x) = cos(x)
			}
			const auto quad = static_cast<int>(
				angle * Constants<double>::twoOverPi); // Get quadrant # (0 to 3) we're in
			switch(quad) {
				case 0: return cos_helper(angle);
				case 1: return -cos_helper(Constants<double>::pi - angle);
				case 2: return -cos_helper(angle - Constants<double>::pi);
				case 3: return cos_helper(Constants<double>::twoPi - angle);
				default: return 0.0;
			}
		}

		/// @brief Fast approximation calculation of sine(angle)
		///
		/// @param angle - The angle to calculate the sine of
		/// @return - The sine of the angle
		[[nodiscard]] static constexpr inline auto sin_internal(double angle) noexcept -> double {
			return cos_internal(Constants<double>::piOver2 - angle);
		}

		/// @brief Helper function for `tan`; Don't use on its own
		///
		/// @param x - the angle
		/// @return tan(x)
		[[nodiscard]] static constexpr inline auto tan_helper(double x) noexcept -> double {
			constexpr double c1 = -34287.4662577359568109624;
			constexpr double c2 = 2566.7175462315050423295;
			constexpr double c3 = -26.5366371951731325438;
			constexpr double c4 = -43656.1579281292375769579;
			constexpr double c5 = 12244.4839556747426927793;
			constexpr double c6 = -336.611376245464339493;

			const auto x2 = x * x; // The input argument squared

			return (x * (c1 + x2 * (c2 + x2 * c3)) / (c4 + x2 * (c5 + x2 * (c6 + x2))));
		}

		/// @brief Fast approximation calculation of tangent(angle)
		///
		/// @param angle - The angle to calculate the tangent of
		/// @return - The tangent of the angle
		[[nodiscard]] static constexpr inline auto tan_internal(double angle) noexcept -> double {
			angle = General::fmod(angle, Constants<double>::twoPi); // Get rid of values >2 *pi
			const auto octant
				= static_cast<int>(angle / Constants<double>::fourOverPi); // Get octant # (0 to 7)
			switch(octant) {
				case 0: return tan_helper(angle * Constants<double>::fourOverPi);
				case 1:
					return 1.0
						   / tan_helper((Constants<double>::piOver2 - angle)
										* Constants<double>::fourOverPi);
				case 2:
					return -1.0
						   / tan_helper((angle - Constants<double>::piOver2)
										* Constants<double>::fourOverPi);
				case 3:
					return -tan_helper((Constants<double>::pi - angle)
									   * Constants<double>::fourOverPi);
				case 4:
					return tan_helper((angle - Constants<double>::pi)
									  * Constants<double>::fourOverPi);
				case 5:
					return 1.0
						   / tan_helper((Constants<double>::threePiOver2 - angle)
										* Constants<double>::fourOverPi);
				case 6:
					return -1.0
						   / tan_helper((angle - Constants<double>::threePiOver2)
										* Constants<double>::fourOverPi);
				case 7:
					return -tan_helper((Constants<double>::twoPi - angle)
									   * Constants<double>::fourOverPi);
				default: return 0.0;
			}
		}

		/// @brief Helper function for `atanf`; Don't use on its own
		///
		/// @param x - the angle
		/// @return atan(x)
		[[nodiscard]] static constexpr inline auto atan_helper(double x) noexcept -> double {
			constexpr double c1 = 48.70107004404898384;
			constexpr double c2 = 49.5326263772254345;
			constexpr double c3 = 9.40604244231624;
			constexpr double c4 = 48.70107004404996166;
			constexpr double c5 = 65.7663163908956299;
			constexpr double c6 = 21.587934067020262;

			const auto x2 = x * x; // The input argument squared

			return (x * (c1 + x2 * (c2 + x2 * c3)) / (c4 + x2 * (c5 + x2 * (c6 + x2))));
		}

		/// @brief Fast approximation calculation of arctangent(angle)
		///
		/// @param angle - The angle to calculate the arctangent of
		/// @return - The arctangent of the angle
		[[nodiscard]] static constexpr inline auto atan_internal(double angle) noexcept -> double {
			const constexpr double tanPiOver6 = tan_internal(Constants<double>::piOver6);
			const constexpr double tanPiOver12 = tan_internal(Constants<double>::piOver12);
			bool complement = false; // true if arg was >1
			bool region = false;	 // true depending on region arg is in
			bool sign = false;		 // true if arg was < 0

			if(angle < 0.0) {
				angle = -angle;
				sign = true; // arctan(-x)=-arctan(x)
			}
			if(angle > 1.0) {
				angle = 1.0 / angle; // keep arg between 0 and 1
				complement = true;
			}
			if(angle > tanPiOver12) {
				angle = (angle - tanPiOver6)
						/ (1.0 + tanPiOver6 * angle); // reduce arg to under tan(pi/12)
				region = true;
			}

			double y = atan_helper(angle); // run the approximation
			if(region) {
				y += Constants<double>::piOver6; // correct for region we're in
			}
			if(complement) {
				y = Constants<double>::piOver2 - y; // correct for 1/x if we did that
			}
			if(sign) {
				y = -y; // correct for negative arg
			}
			return y;
		}

		/// @brief Fast approximation calculation of the hyperbolic tangent ("tanch") of the angle
		///
		/// @param angle - The angle to calculate the hyperbolic tanget of
		/// @return - The hyperbolic tangent of the angle
		[[nodiscard]] static constexpr inline auto tanh_internal(double angle) noexcept -> double {
			if(angle < 0.0) {
				angle *= -1.0;
				return -(-0.67436811832e-5
						 + (0.2468149110712040
							+ (0.0583691066395175 + 0.03357335044280075 * angle) * angle)
							   * angle)
					   / (0.2464845986383725
						  + (0.0609347197060491
							 + (0.1086202599228572 + 0.02874707922475963 * angle) * angle)
								* angle);
			}
			else {
				return (-0.67436811832e-5
						+ (0.2468149110712040
						   + (0.0583691066395175 + 0.03357335044280075 * angle) * angle)
							  * angle)
					   / (0.2464845986383725
						  + (0.0609347197060491
							 + (0.1086202599228572 + 0.02874707922475963 * angle) * angle)
								* angle);
			}
		}
	};
} // namespace math
