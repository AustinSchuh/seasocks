#include "seasocks/json.h"

namespace SeaSocks {

void jsonToStream(std::ostream& str, const char* t) {
	str << '"';
	for (; *t; ++t) {
		switch (*t) {
		default:
			str << *t;
			break;
		case '"':
		case '\\':
			str << '\\';
			str << *t;
			break;
		}
	}
	str << '"';
}

void jsonToStream(std::ostream& str, const EpochTimeAsLocal& t) {
	str << "new Date(" << t.t * 1000 << ").toLocaleString()";
}

}  // SeaSocks
