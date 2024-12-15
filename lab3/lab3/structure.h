#pragma once
#include <unordered_set>
#include "cs.h"
#include "pipe.h"

struct Connection {
    int csInput;    // ������ ������� ��
    int pipe;       // ������ �����
    int csOutput;   // ������ �������� ��

    Connection(int csInput, int pipe, int csOutput)
        : csInput(csInput), pipe(pipe), csOutput(csOutput) {}

    bool operator==(const Connection& other) const {
        return csInput == other.csInput && pipe == other.pipe && csOutput == other.csOutput;
    }

    struct Hash {
        size_t operator()(const Connection& c) const {
            return hash<int>()(c.csInput) ^ hash<int>()(c.pipe) ^ hash<int>()(c.csOutput);
        }
    };
};
