#!/bin/bash

# Chess Analyzer Test Runner
# Runs all tests sequentially to avoid log file collisions

# Colors for output
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
NC='\033[0m' # No Color

# Directories
TEST_DIR="./tests"
LOGS_DIR="./logs"
EXECUTABLE="./analyzer"

# Statistics
PASSED=0
FAILED=0
TOTAL=0

# ============================================================================
# Helper Functions
# ============================================================================

print_header() {
    echo -e "\n${BLUE}================================${NC}"
    echo -e "${BLUE}$1${NC}"
    echo -e "${BLUE}================================${NC}\n"
}

print_success() {
    echo -e "${GREEN}✓ $1${NC}"
    ((PASSED++))
}

print_failure() {
    echo -e "${RED}✗ $1${NC}"
    ((FAILED++))
}

print_info() {
    echo -e "${YELLOW}ℹ $1${NC}"
}

# ============================================================================
# Main Script
# ============================================================================

print_header "Chess Analyzer Test Suite"

# Check if executable exists
if [ ! -f "$EXECUTABLE" ]; then
    print_info "Building project..."
    make
    if [ ! -f "$EXECUTABLE" ]; then
        print_failure "Failed to build executable"
        exit 1
    fi
    print_success "Build successful"
fi

# Clear and recreate logs directory
if [ -d "$LOGS_DIR" ]; then
    rm -rf "$LOGS_DIR"
fi
mkdir -p "$LOGS_DIR"
print_info "Logs directory cleared and ready"

# List of test files
TEST_FILES=(
    "mate1.chess"
    "mate2.chess"
    "mate3.chess"
    "mate4.chess"
    "stalemate.chess"
    "checkmate.chess"
    "empty.chess"
    "invalid_piece.chess"
    "invalid_pos.chess"
    "duplicate_pos.chess"
    "pawn_first_rank.chess"
    "two_white_kings.chess"
)

# Define expected outcomes for each test
declare -A EXPECTED_OUTCOME
declare -A EXPECTED_DEPTH

# Mate tests (should succeed)
EXPECTED_OUTCOME["mate1.chess"]="success"
EXPECTED_DEPTH["mate1.chess"]=1

EXPECTED_OUTCOME["mate2.chess"]="success"
EXPECTED_DEPTH["mate2.chess"]=2

EXPECTED_OUTCOME["mate3.chess"]="success"
EXPECTED_DEPTH["mate3.chess"]=3

EXPECTED_OUTCOME["mate4.chess"]="success"
EXPECTED_DEPTH["mate4.chess"]=4

# Stalemate test (should succeed)
EXPECTED_OUTCOME["stalemate.chess"]="stalemate"
EXPECTED_DEPTH["stalemate.chess"]=2

# Checkmate test (already in mate - but valid position format, so not an error)
EXPECTED_OUTCOME["checkmate.chess"]="success"
EXPECTED_DEPTH["checkmate.chess"]=1

# Error tests (should fail)
EXPECTED_OUTCOME["empty.chess"]="error"
EXPECTED_OUTCOME["invalid_piece.chess"]="error"
EXPECTED_OUTCOME["invalid_pos.chess"]="error"
EXPECTED_OUTCOME["duplicate_pos.chess"]="error"
EXPECTED_OUTCOME["pawn_first_rank.chess"]="error"
EXPECTED_OUTCOME["two_white_kings.chess"]="error"

print_header "Running Tests"

# Run each test
for test_file in "${TEST_FILES[@]}"; do
    TEST_PATH="$TEST_DIR/$test_file"
    
    if [ ! -f "$TEST_PATH" ]; then
        print_failure "$test_file (file not found)"
        ((TOTAL++))
        continue
    fi
    
    ((TOTAL++))
    
    # Get expected outcome and depth for this test
    expected="${EXPECTED_OUTCOME[$test_file]}"
    depth="${EXPECTED_DEPTH[$test_file]:-1}"
    
    echo -e "\n${YELLOW}Testing: $test_file${NC}"
    echo "  Expected: $expected (depth: $depth)"
    echo "  Running: $EXECUTABLE $TEST_PATH $depth"
    
    # Run the test and capture output
    OUTPUT=$("$EXECUTABLE" "$TEST_PATH" "$depth" 2>&1)
    EXIT_CODE=$?
    
    # Evaluate test result
    if [[ "$expected" == "error" ]]; then
        if [ $EXIT_CODE -ne 0 ]; then
            print_success "$test_file"
        else
            print_failure "$test_file (expected error, but succeeded)"
        fi
    else
        if [ $EXIT_CODE -eq 0 ]; then
            # Check for expected keywords in output
            if [[ "$expected" == "stalemate" && "$OUTPUT" == *"forces stalemate"* ]]; then
                print_success "$test_file ($expected)"
            elif [[ "$expected" == "success" && "$OUTPUT" == *"mates"* ]]; then
                print_success "$test_file (mate found)"
            else
                print_failure "$test_file (exit 0 but didn't find expected outcome)"
                echo "    Output: $(echo "$OUTPUT" | head -1)"
            fi
        else
            print_failure "$test_file (expected success, but failed with exit code $EXIT_CODE)"
        fi
    fi
    
    # Brief pause between tests to ensure log file timestamps are unique
    sleep 0.5
done

# ============================================================================
# Summary
# ============================================================================

print_header "Test Summary"

echo "Total tests:  $TOTAL"
echo -e "Passed:       ${GREEN}$PASSED${NC}"
echo -e "Failed:       ${RED}$FAILED${NC}"

if [ $FAILED -eq 0 ]; then
    echo -e "\n${GREEN}All tests passed!${NC}\n"
    exit 0
else
    echo -e "\n${RED}Some tests failed.${NC}\n"
    exit 1
fi
