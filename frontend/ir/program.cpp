// SPDX-License-Identifier: MPL-2.0
// Copyright © 2021 yuzu Emulator Project (https://github.com/yuzu-emu/yuzu/)

#include <map>
#include <string>

#include <fmt/format.h>

#include <shader_compiler/frontend/ir/basic_block.h>
#include <shader_compiler/frontend/ir/program.h>
#include <shader_compiler/frontend/ir/value.h>

namespace Shader::IR {

std::string DumpProgram(const Program& program) {
    size_t index{0};
    std::map<const IR::Inst*, size_t> inst_to_index;
    std::map<const IR::Block*, size_t> block_to_index;

    for (const IR::Block* const block : program.blocks) {
        block_to_index.emplace(block, index);
        ++index;
    }
    std::string ret;
    for (const auto& block : program.blocks) {
        ret += IR::DumpBlock(*block, block_to_index, inst_to_index, index) + '\n';
    }
    return ret;
}

void ResetProgram(Program& program) {
    for (IR::Block* const block : program.blocks) {
        for (IR::Inst& inst : block->Instructions()) {
            inst.Reset();
        }
    }
}

} // namespace Shader::IR
