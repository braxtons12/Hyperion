/// based on https://mklimenko.github.io/english/2018/06/04/constexpr-random/
#pragma once

#include <atomic>
#include <cstdint>
#include <gsl/gsl>
#include <limits>
#include <random>

#include "../utils/Concepts.h"

namespace math {
	using gsl::narrow_cast;
#ifndef _MSC_VER
	using std::size_t;
#endif //_MSC_VER

// clang-format off
#ifndef _MSC_VER
	// NOLINTNEXTLINE
	#define IGNORE_DATETIME_START \
		_Pragma("GCC diagnostic push") \
		_Pragma("GCC diagnostic ignored \"-Wdate-time\"")
#else
	// NOLINTNEXTLINE
	#define IGNORE_DATETIME_START
#endif
// clang-format on

// clang-format off
#ifndef _MSC_VER
	// NOLINTNEXTLINE
	#define IGNORE_DATETIME_STOP \
		_Pragma("GCC diagnostic pop")
#else
	// NOLINTNEXTLINE
	#define IGNORE_DATETIME_STOP
#endif
	// clang-format on

// clang-format off
#ifndef _MSC_VER
	// NOLINTNEXTLINE
	#define IGNORE_WEAK_VTABLES_START \
		_Pragma("GCC diagnostic push") \
		_Pragma("GCC diagnostic ignored \"-Wweak-vtables\"")
#else
	// NOLINTNEXTLINE
	#define IGNORE_WEAK_VTABLES_START
#endif
// clang-format on

// clang-format off
#ifndef _MSC_VER
	// NOLINTNEXTLINE
	#define IGNORE_WEAK_VTABLES_STOP \
		_Pragma("GCC diagnostic pop")
#else
	// NOLINTNEXTLINE
	#define IGNORE_WEAK_VTABLES_STOP
#endif
	// clang-format on

	IGNORE_WEAK_VTABLES_START
	class Engine {
	  public:
		constexpr Engine() noexcept = default;
		constexpr Engine(const Engine& engine) noexcept = default;
		constexpr Engine(Engine&& engine) noexcept = default;
		virtual constexpr ~Engine() noexcept = default;

		[[nodiscard]] virtual constexpr auto get_seed() const noexcept -> size_t = 0;
		virtual constexpr auto seed(size_t seed) noexcept -> void = 0;
		virtual constexpr auto generate() noexcept -> size_t = 0;

		template<size_t size>
		inline constexpr auto generate_array() noexcept -> std::array<size_t, size> {
			auto array = std::array<size_t, size>();
			for(auto& element : array) {
				element = generate();
			}
		}

		[[nodiscard]] virtual constexpr auto max_value() const noexcept -> size_t = 0;

		constexpr auto operator=(const Engine& engine) noexcept -> Engine& = default;
		constexpr auto operator=(Engine&& engine) noexcept -> Engine& = default;

		virtual constexpr auto operator()() noexcept -> size_t = 0;
	};
	IGNORE_WEAK_VTABLES_STOP

	template<size_t max = 714025>
	class LinearCongruentialEngine final : public Engine {
	  public:
		constexpr LinearCongruentialEngine() noexcept = default;
		constexpr LinearCongruentialEngine(
			const LinearCongruentialEngine& engine) noexcept = default;
		constexpr LinearCongruentialEngine(LinearCongruentialEngine&& engine) noexcept = default;
		constexpr ~LinearCongruentialEngine() noexcept final = default;

		IGNORE_DATETIME_START
		[[nodiscard]] inline constexpr auto get_seed() const noexcept -> size_t final {
			const auto* t = __TIME__;
			return time_from_string(t, 0) * 60 * 60 + time_from_string(t, 3) * 60
				   + time_from_string(t, 6);
		}
		IGNORE_DATETIME_STOP

		inline constexpr auto seed(size_t seed) noexcept -> void final {
			m_previous = seed;
		}

		[[nodiscard]] inline constexpr auto generate() noexcept -> size_t final {
			m_previous = (m_a * m_previous + m_c) % max;
			return m_previous;
		}

		[[nodiscard]] inline constexpr auto max_value() const noexcept -> size_t final {
			return max;
		}

		constexpr auto operator=(const LinearCongruentialEngine& engine) noexcept
			-> LinearCongruentialEngine& = default;
		constexpr auto operator=(LinearCongruentialEngine&& engine) noexcept
			-> LinearCongruentialEngine& = default;

		inline constexpr auto operator()() noexcept -> size_t final {
			return generate();
		}

	  private:
		size_t m_a = 4096;
		size_t m_c = 150889;
		size_t m_previous = get_seed();

		[[nodiscard]] static inline constexpr auto
		time_from_string(const char* string, int offset) noexcept -> size_t {
			return narrow_cast<size_t>(string[offset] - '0') * 10	// NOLINT
				   + narrow_cast<size_t>(string[offset + 1] - '0'); // NOLINT
		}
	};

	IGNORE_WEAK_VTABLES_START
	template<typename EngineType, utils::concepts::Numeric T = int>
	requires utils::concepts::Derived<EngineType, Engine>
	class Distribution {
	  public:
		constexpr Distribution() noexcept = default;
		constexpr Distribution(const Distribution& distribution) noexcept = default;
		constexpr Distribution(Distribution&& distribution) noexcept = default;
		virtual constexpr ~Distribution() noexcept = default;

		virtual constexpr auto normalized_random_value() noexcept -> double = 0;
		virtual constexpr auto random_value() noexcept -> T = 0;
		template<size_t size>
		inline constexpr auto normalized_random_values() noexcept -> std::array<double, size> {
			auto array = std::array<double, size>();
			for(auto& element : array) {
				element = normalized_random_value();
			}

			return array;
		}
		template<size_t size>
		inline constexpr auto random_values() noexcept -> std::array<T, size> {
			auto array = std::array<T, size>();
			for(auto& element : array) {
				element = random_value();
			}

			return array;
		}
		virtual constexpr auto seed(size_t seed) noexcept -> void = 0;
		[[nodiscard]] virtual constexpr auto get_seed() noexcept -> size_t = 0;

		[[nodiscard]] virtual constexpr auto get_min() const noexcept -> T = 0;
		virtual constexpr auto set_min(T min) noexcept -> void = 0;
		[[nodiscard]] virtual constexpr auto get_max() const noexcept -> T = 0;
		virtual constexpr auto set_max(T max) noexcept -> void = 0;

		constexpr auto
		operator=(const Distribution& distribution) noexcept -> Distribution& = default;
		constexpr auto operator=(Distribution&& distribution) noexcept -> Distribution& = default;

		virtual constexpr auto operator()() noexcept -> T = 0;
	};
	IGNORE_WEAK_VTABLES_STOP

	template<typename EngineType, utils::concepts::Numeric T = int>
	requires utils::concepts::Derived<EngineType, Engine>
	class UniformDistribution final : public Distribution<EngineType, T> {
	  public:
		constexpr UniformDistribution() noexcept requires
			utils::concepts::DefaultConstructible<EngineType>
			: m_engine(std::make_unique<EngineType>()) {
			m_engine->seed(m_engine->get_seed());
		}
		constexpr UniformDistribution(T min, T max) noexcept requires
			utils::concepts::DefaultConstructible<EngineType>
			: m_min(min), m_max(max), m_engine(std::make_unique<EngineType>()) {
			m_engine->seed(m_engine->get_seed());
		}
		constexpr UniformDistribution(T min, T max, std::unique_ptr<EngineType>&& engine) noexcept
			: m_min(min), m_max(max), m_engine(engine) {
			m_engine->seed(m_engine->get_seed());
		}
		explicit constexpr UniformDistribution(std::unique_ptr<EngineType>&& engine) noexcept
			: m_engine(std::move(engine)) {
			m_engine->seed(m_engine->get_seed());
		}
		template<typename... Args>
		requires utils::concepts::Derived<EngineType, Engine> && utils::concepts::
			ConstructibleFrom<EngineType, Args...>
		explicit constexpr UniformDistribution(Args&&... args) noexcept
			: m_engine(std::make_unique<EngineType>(args...)) {
			m_engine->seed(m_engine->get_seed());
		}
		template<typename... Args>
		requires utils::concepts::Derived<EngineType, Engine> && utils::concepts::
			ConstructibleFrom<EngineType, Args...>
		explicit constexpr UniformDistribution(T min, T max, Args&&... args) noexcept
			: m_min(min), m_max(max), m_engine(std::make_unique<EngineType>(args...)) {
			m_engine->seed(m_engine->get_seed());
		}
		constexpr UniformDistribution(const UniformDistribution& distribution) noexcept = default;
		constexpr UniformDistribution(UniformDistribution&& distribution) noexcept = default;

		constexpr ~UniformDistribution() noexcept final = default;

		inline constexpr auto normalized_random_value() noexcept -> double final {
			return narrow_cast<double>(m_engine->generate())
				   / narrow_cast<double>(m_engine->max_value());
		}

		inline constexpr auto random_value() noexcept -> T final {
			return narrow_cast<T>(this->normalized_random_value()) * (m_max - m_min) + m_min;
		}

		inline constexpr auto seed(size_t seed) noexcept -> void final {
			m_engine->seed(seed);
		}

		[[nodiscard]] inline constexpr auto get_seed() noexcept -> size_t final {
			return m_engine->get_seed();
		}

		inline constexpr auto set_min(T min) noexcept -> void final {
			m_min = min;
		}
		[[nodiscard]] inline constexpr auto get_min() const noexcept -> T final {
			return m_min;
		}

		inline constexpr auto set_max(T max) noexcept -> void final {
			m_max = max;
		}
		[[nodiscard]] inline constexpr auto get_max() const noexcept -> T final {
			return m_max;
		}

		constexpr auto operator=(const UniformDistribution& distribution) noexcept
			-> UniformDistribution& = default;
		constexpr auto
		operator=(UniformDistribution&& distribution) noexcept -> UniformDistribution& = default;

		inline constexpr auto operator()() noexcept -> T final {
			return random_value();
		}

	  private:
		T m_min = narrow_cast<T>(0);
		T m_max = narrow_cast<T>(1);
		std::unique_ptr<EngineType> m_engine;
	};

	template<utils::concepts::Numeric T = float>
	[[clang::no_destroy]] static math::UniformDistribution<math::LinearCongruentialEngine<>, T>
		GLOBAL_UNIFORM_DISTRIBUTION;

	template<utils::concepts::Numeric T = float>
	static std::atomic_bool GLOBAL_UNIFORM_DISTRIBUTION_INITIALIZED;

	template<utils::concepts::Numeric T = float>
	inline static constexpr auto initialize_global_uniform_distribution() noexcept -> void {
		bool initialized = false;
		if(GLOBAL_UNIFORM_DISTRIBUTION_INITIALIZED<T>.compare_exchange_strong(
			   initialized,
			   true,
			   std::memory_order_seq_cst))
		{
			GLOBAL_UNIFORM_DISTRIBUTION<
				T> = math::UniformDistribution<math::LinearCongruentialEngine<>, T>();
		}
	}

	template<utils::concepts::FloatingPoint T = float>
	inline auto random_value() noexcept -> T {
		initialize_global_uniform_distribution<T>();
		GLOBAL_UNIFORM_DISTRIBUTION<T>.set_min(narrow_cast<T>(0));
		GLOBAL_UNIFORM_DISTRIBUTION<T>.set_max(narrow_cast<T>(1));

		return GLOBAL_UNIFORM_DISTRIBUTION<T>();
	}

	template<utils::concepts::Numeric T = float>
	inline auto random_value(T min, T max) noexcept -> T {
		initialize_global_uniform_distribution<T>();

		GLOBAL_UNIFORM_DISTRIBUTION<T>.set_min(min);
		GLOBAL_UNIFORM_DISTRIBUTION<T>.set_max(max);

		return GLOBAL_UNIFORM_DISTRIBUTION<T>();
	}
} // namespace math
