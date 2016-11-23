function [f,C,cW,L] = cepsDWT(x,fs,silenceThreshold,peakLowerThreshold,dwtLevels)
%CEPSDWT Finds pitch frequency in given sample frame
%   x - sample frame, must be power of two
%   fs - sample frequency
%   silenceThreshold - RMS threshold for which sample frame is considered
%       to be nothing mor than silence
%   peakLowerThreshold - Threshold relative to the max peak in approximated 
%       cepstrum. Peak range begins at first element to be below this
%       threshold and ends after second to be below this element after a
%       local maximum has been located.
%   dwtLevels - number of times to approximate and downscale the cepstrum
%       data in order to avoid noisy peaks. 2-3 recommended.
%
%   f - pitch frequency, returns 0 Hz if sample frame is considered silent
%   C - cepstrum
%   cW - DWT transform of cepstrum, including the latest approximation
%       coefficients and all the detail coefficients.
%   L - vector specifying the length of each vector of coefficients in the
%       DWT.

if sqrt(mean(x.^2)) <= silenceThreshold
    f = 0;
    return;
end

C = abs(ifft(20*log(abs(fft(x))))).^2;

[cW,L] = wavedec(C,dwtLevels,'db1');

cAn = cW(1:L(1));

r = floor(L(1)/2);
a = find(cAn(1:r) <= peakLowerThreshold*max(cAn(1:r)),1);
b = find(cAn(a+1:r) >= max(cAn(a+1:r)),1)+a;
c = find(cAn(b+1:r) <= peakLowerThreshold*max(cAn(1:a)),1)+b;

k1 = 2^(dwtLevels)*(a-1)+1;
k2 = 2^(dwtLevels)*(c-1)+1;

k = find(C(k1:k2) >= max(C(k1:k2)),1)+k1-1;
f = fs/(k-1);

end

