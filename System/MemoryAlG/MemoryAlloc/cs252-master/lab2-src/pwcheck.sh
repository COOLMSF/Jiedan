#!/bin/bash

#DO NOT REMOVE THE FOLLOWING TWO LINES
git add $0 >> .local.git.out
git commit -a -m "Lab 2 commit" >> .local.git.out
git push >> .local.git.out || echo

#Your code here
DEBUG="false"

evaluatePassword()
{
    password=$1
    length="${#password}"
    score=0

    [ "$DEBUG" == true ] && echo "Password: $password"
    [ "$DEBUG" == "true" ] && echo "Length: $length"


    if [[ "$length" -lt 6 ]] || [[ "$length" -gt 32 ]]; then
        echo "Error: Password length invalid."
        return 1
    else
        [ "$DEBUG" == "true" ] && echo "Valid +$length"
        score="$(($score + $length))"
    fi

    if [[ "$password" =~ [#$+%@] ]]; then
        [ "$DEBUG" == "true" ] && echo "Found special chars +5"
        score="$(($score + 5))"
    fi

    if [[ "$password" =~ [0-9] ]]; then
        [ "$DEBUG" == "true" ] && echo "Found number(s) +5"
        score="$(($score + 5))"
    fi

    if [[ "$password" =~ [A-Za-z] ]]; then
        [ "$DEBUG" == "true" ] && echo "Found letter(s) +5"
        score="$(($score + 5))"
    fi

    echo "$password" | grep -E '([A-Za-z0-9])\1{1,}' >/dev/null
    if [[ "$?" -eq 0 ]]; then
        [ "$DEBUG" == "true" ] && echo "Found repeated alphanumeric characters -10"
        score="$(($score - 10))"
    fi

    echo "$password" | grep -E '([a-z]){3,}' >/dev/null
    if [[ "$?" -eq 0 ]]; then
        [ "$DEBUG" == "true" ] && echo "Found 3+ consecutive lowercase characters -3"
        score="$(($score - 3))"
    fi

    echo "$password" | grep -E '([A-Z]){3,}' >/dev/null
    if [[ "$?" -eq 0 ]]; then
        [ "$DEBUG" == "true" ] && echo "Found 3+ consecutive uppercase characters -3"
        score="$(($score - 3))"
    fi

    echo "$password" | grep -E '([0-9]){3,}' >/dev/null
    if [[ "$?" -eq 0 ]]; then
        [ "$DEBUG" == "true" ] && echo "Found 3+ consecutive numerals -3"
        score="$(($score - 3))"
    fi

    echo -e "Password Score: $score"
}

if [[ -s "$1" ]]; then
    while IFS='' read -r line || [[ -n "$line" ]]; do
        evaluatePassword "$line"

        if [[ "$?" -ne 0 ]]; then
            [ "$DEBUG" == "true" ] && echo "Should exit now"
            exit 1
        fi
        [ "$DEBUG" == "true" ] && echo ""
    done <"$1"
fi
