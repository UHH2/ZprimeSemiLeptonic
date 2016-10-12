#!/bin/bash

##This is a simple example of a SGE batch script
##Use home server with scientific linux 6 
#$ -l os=sld6 
#$ -l site=hh 
#$ -cwd
##You need to set up sframe
#$ -V 
##email Notification
#$ -m as
#$ -M xxxx.edu
##running in local mode with 8-12 cpu slots
##$ -pe local 8-12
##CPU memory
#$ -l h_vmem=2G
##DISK memory
#$ -l h_fsize=2G   
cd workdir
sframe_main WJets_HT2500ToInf__L_${SGE_TASK_ID}.xml
