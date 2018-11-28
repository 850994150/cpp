#!/bin/bash

read color

case "$color" in
    blue)
        echo $color is blue
        ;;
    green)
        echo $color is green
        ;;
    red|orange)
        echo $color is red orange
        ;;
    *)
        echo "Not a color"
esac
