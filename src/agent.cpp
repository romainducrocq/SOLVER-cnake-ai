#include "../include/agent.h"

Agent::Agent(int cols, int rows)
    : m_cols(cols), m_rows(rows), m_hcycle(cols, rows){}
