# EEG-video Monitoring
This project aims to generate a tool to visualize continuous EEG (Electroencephalography) recorded for a prolonged period with simultaneous video recordings. 4 channels of EEG signals includes Fp1, Fp2, F3, and F4, which are on the frontal region, are ploted in teh video. A public dataset of EEG signal collectd by _Bahareh Rahmani_ is used in this project to generate example videos. The link of the public dataset is shown as following:

https://figshare.com/articles/dataset/EEG_Data/5393338/1

# Installs
The project was only developed and tested under the Debian-based systems. This project makes calls to *jgraph* (generate figrues of EEG signal plot), *ps2pdf* (converting the jgraph outputs to PDF), *convert* (converting the PDF to JPEG) and ffmpeg (creating the mp4 video from mutilple jpeg images). 

```
UNIX>sudo apt-get install jgraph ghostscript imagemagick ffmpeg

```
If you install convert directly from imagemegick, *policy.xml* in ImageMagick-7 needs to be changed for converting from PDF to JPEG. To do so, you need to edit as following:
1. Open the policy.xml file in terminal 
```
sudo nano /etc/ImageMagick-6/policy.xml

```
2. Find <policy domain = "coder" rights ="none pattern ="PDF" /> and replace none with read|write. 
  
# How to use
1. Use terminal to open the eeg file in a Debian-based system. 
2. The system will ask teh inputfile name, type teh name of targeted EEG signal file in terminal.
3. The system will then ask input about duration time, which is the time of duration of EEG signal. Input how many minutes you want by a integer number.
4. The system will then run, and output a Output.mp4 fill in the folder.

Some examples of the output videos are in the example folder.
