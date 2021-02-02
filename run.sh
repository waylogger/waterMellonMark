#!/bin/bash



(make >> /dev/null) && echo `./index`; rm index
