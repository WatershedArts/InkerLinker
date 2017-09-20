#!/bin/sh
#--------------------------------------------------------------
#  getaddons.sh
#  InkerLinker
#  Created by David Haylock on 19/09/2017.
#! InkerLinker.
#--------------------------------------------------------------

repobase="https://github.com";
repos="kylemcdonald/ofxAudioDecoder \
andreasmuller/ofxAutoReloadedShader \
kritzikratzi/ofxAvCodec \
kylemcdonald/ofxDmx \
armadillu/ofxFontStash \
bakercp/ofxHTTP \
arturoc/ofxHttpUtils \
jeffcrouse/ofxJSON \
bakercp/ofxIO \
bakercp/ofxMediaType \
bakercp/ofxNetworkUtils \
bakercp/ofxSSLManager \
NickHardeman/ofxSvgLoader \
bakercp/ofxTaskQueue \
arturoc/ofxTween \
DHaylock/ofxTouchBoard \
";

echo "---------------------------";
echo "Getting Addons";

cd ../../addons;

pwd;

for repo in ${repos};
do
	if [ ! -d "${repo}" ]; then
		git clone "${repobase}/${repo}.git";
		repomaker="$(cut -d'/' -f1 <<< "${repo}")";
		addonname="$(cut -d'/' -f2 <<< "${repo}")";
		echo "Getting ${addonname}";
		if [ "${repomaker}" == "bakercp" ]; then
			echo "Checkout Stable Branch";
			cd "${addonname}";
			pwd;
			git checkout origin/stable;
			cd ..;
		fi

	else 
		echo "Pulling ${repo}";
		cd "${addonname}";
		pwd;
		echo "Pull";
		cd ..;
	fi
done

echo "Done";
exit;