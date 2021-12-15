#!/bin/bash

scram b clean
make clean
scram b -j8
make -j8
