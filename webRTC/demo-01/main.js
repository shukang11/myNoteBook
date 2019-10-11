'use strict';

var constraints = {
    audio: false,
    video: true
};

var video = document.querySelector('video');
const canvas = window.canvas = document.querySelector('canvas');
canvas.width = 480;
canvas.height = 360;

const button = document.querySelector('buttong');
var snapshootEvent = function() {
    canvas.width = video.videoWidth;
    canvas.height = video.videoHeight;
    canvas.getContext('2d').drawImage(video, 0, 0, canvas.width, canvas.height);
}

function handleSuccess(stream) {
    video.srcObject = stream;
};

function handleError(error) {
    console.error('getUserMedia error: ', error);
};

async function init() {
    console.log('ss');
    
    try {
        const stream = await navigator.mediaDevices.getUserMedia(constraints);
        handleSuccess(stream);
    }catch (e) {
        handleError(e)
    }
};

init();