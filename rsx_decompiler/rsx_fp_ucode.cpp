#include "rsx_fp_ucode.h"

namespace rsx
{
	namespace fragment_program
	{
		const std::string input_attrib_names[16] =
		{
			"wpos", //0
			"col0", //1
			"col1", //2
			"fogc", //3
			"tex0", //4
			"tex1", //5
			"tex2", //6
			"tex3", //7
			"tex4", //8
			"tex5", //9
			"tex6", //10
			"tex7", //11
			"tex8", //12
			"tex9", //13
			"ssa", //14
			"unk"  //15
		};

		const std::string instructions_names[128] =
		{
			"NOP", "MOV", "MUL", "ADD", "MAD", "DP3", "DP4",
			"DST", "MIN", "MAX", "SLT", "SGE", "SLE", "SGT",
			"SNE", "SEQ", "FRC", "FLR", "KIL", "PK4", "UP4",
			"DDX", "DDY", "TEX", "TXP", "TXD", "RCP", "RSQ",
			"EX2", "LG2", "LIT", "LRP", "STR", "SFL", "COS",
			"SIN", "PK2", "UP2", "POW", "PKB", "UPB", "PK16",
			"UP16", "BEM", "PKG", "UPG", "DP2A", "TXL", "NULL",
			"TXB", "NULL", "TEXBEM", "TXPBEM", "BEMLUM", "REFL", "TIMESWTEX",
			"DP2", "NRM", "DIV", "DIVSQ", "LIF", "FENCT", "FENCB",
			"NULL", "BRK", "CAL", "IFE", "LOOP", "REP", "RET"
		};

		std::uint64_t hash(const ucode_instr *ucode)
		{
			std::uint64_t hash = 0xCBF29CE484222325ULL;

			for (const ucode_instr *ptr = ucode; !ptr->end(); ++ptr)
			{
				hash ^= ptr->dst._u32 | (std::uint64_t(ptr->src0._u32) << 32);
				hash += (hash << 1) + (hash << 4) + (hash << 5) + (hash << 7) + (hash << 8) + (hash << 40);

				hash ^= ptr->src1._u32 | (std::uint64_t(ptr->src2._u32) << 32);
				hash += (hash << 1) + (hash << 4) + (hash << 5) + (hash << 7) + (hash << 8) + (hash << 40);

				if (ptr->has_constant())
					++ptr;
			}

			return hash;
		}
	}
}
