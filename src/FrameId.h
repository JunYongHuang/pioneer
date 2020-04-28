#ifndef FRAMEID_H_INCLUDED
#define FRAMEID_H_INCLUDED

#include <cstddef>
#include <cstdint>
#include <exception>
#include <limits>

struct FrameId {
	static constexpr uint32_t Invalid = std::numeric_limits<uint32_t>::max();
	constexpr FrameId() :
		m_id(Invalid) {}
	constexpr FrameId(uint32_t new_id) :
		m_id(new_id) {}

	constexpr operator bool() const { return m_id != Invalid; }
	constexpr operator uint32_t() const { return m_id; }
	constexpr operator size_t() const { return m_id; }

	constexpr bool operator==(FrameId rhs) const { return m_id == rhs.m_id; }
	constexpr bool operator!=(FrameId rhs) const { return m_id != rhs.m_id; }

	constexpr bool valid() const { return m_id != Invalid; }
	constexpr size_t id() const {
		// Cannot use an `if` in constexpr context in C++11, sorry
		return valid() ? static_cast<size_t>(m_id) : (std::terminate(), 0);
	}
	constexpr int unchecked_id() const { return m_id; }

private:
	uint32_t m_id;
};

static_assert(sizeof(FrameId) == sizeof(uint32_t) && alignof(FrameId) == alignof(uint32_t),
	"Error: FrameId sized differently than the underlying type on this platform!");

#endif // FRAMEID_H_INCLUDED
