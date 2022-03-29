#include "myffmpeglib.h"
#include <stdlib.h>
#include <libavformat/avformat.h>
#include <libavcodec/avcodec.h>
#include <libavutil/avutil.h>
#include <libavutil/channel_layout.h>
#include <libavutil/opt.h>
#include <libavdevice/avdevice.h>


	//enum AVCodecID codec_id = 0;

	typedef int BOOL;
	#define TRUE 1
	#define FALSE 0

	#define MyDefine_Decoder_Handle void*

//#ifdef _WIN32
//#define CE_API  __declspec(dllexport)
//#define CE_APICALL  __stdcall
//#else
#define CE_API
#define CE_APICALL
//#endif
#define AAC_DEBUG 1
typedef struct
{
	void* dataPtr;
	unsigned int length;
}AudioBuffer;
typedef enum
{
	MyDefine_CODEC_NONE = 0,
	MyDefine_CODEC_H264 = 0x1C,
	MyDefine_CODEC_H265 = 0xAE,
	MyDefine_CODEC_MJPEG = 0x08,
	MyDefine_CODEC_MPEG4 = 0x0D,
	MyDefine_CODEC_AAC = 0x15002,
	MyDefine_CODEC_G711U = 0x10006,
	MyDefine_CODEC_G711A = 0x10007,
	MyDefine_CODEC_G726 = 0x1100B,
	MyDefine_CODEC_G726LE = 0x11804,
}MyDefine_CodecType;
typedef struct
{
	MyDefine_CodecType VCodec;
	MyDefine_CodecType ACodec;
	unsigned char	FramesPerSecond;
	unsigned short	Width;
	unsigned short  Height;
	unsigned int	VideoBitrate;
	unsigned int	SampleRate;
	unsigned int	Channels;
	unsigned int	BitsPerSample;
	unsigned int	AudioBitrate;
	unsigned int    bits_per_coded_sample;
}MyDefine_FrameInfo;
typedef struct
{
	AVCodecContext* VDecoder;	// 视频解码器
	AVCodecContext* ADecoder;	// 音频解码器
	AVFrame* VFrame;// 解码后的视频帧 音视频帧对象分别定义，防止多线程分别解码音视频造成读写冲突
	AVFrame* AFrame;// 解码后的音频帧
	int PixelSize;// 视频的像素大小
}MyDefineDecoder;
// 编码器结构体定义
typedef struct
{
	// 视频编码器
	AVCodecContext* VEncoder;
	// 音频编码器
	AVCodecContext* AEncoder;
	// 编码后的视频帧 音视频帧对象分别定义，防止多线程分别编码音视频造成读写冲突
	AVFrame* VFrame;
	// 编码前的音频帧
	AVFrame* AFrame;
	// AAC中需要用到的ADTS头信息
	unsigned char AdtsHeader[7];
	// 接收PCM字节个数上限
	int PcmSize;
	// 每组PCM数据的字节数
	int PerPcmSize;
}MyDefineEncoder;

typedef struct
{
	unsigned int (*GetMaxOutputBytes)(PcmToAacStruct* audioTranslateStruct);
	unsigned int (*GetPCMBufferSize)(PcmToAacStruct* audioTranslateStruct);
	faacEncHandle hEncoder;
	faacEncConfigurationPtr pConfiguration;

	unsigned int m_nPCMBitSize;
	unsigned long m_nInputSamples;
	unsigned long m_nMaxOutputBytes;
	int  (*faacEncClose)(faacEncHandle hEncoder);
	BOOL(*Init)(int SampleRate, int channels, int PCM_BITS);

	int (*PcmToAacEncode)(PcmToAacStruct* pcmToAacStruct,int32_t* pbPCMBuffer, unsigned int nPCMBufferSize, unsigned char* pbAACBuffer, unsigned int nMaxOutputBytes);
}PcmToAacStruct;


typedef struct
{
	uint32_t codec_type;
	uint32_t audioChannel;
	uint32_t audioSampleRate;
	uint32_t m_samplingBit;
	uint32_t m_audio_frameLength;
	uint32_t m_type;
	uint32_t config_m_audio_Rate;
	uint32_t config_m_audio_channels;
	PcmToAacStruct* m_pPCMToAAC;
	PcmToAacStruct* m_pPCMToAAC_download;
	MyDefine_Decoder_Handle handle;
	void* pbAACBuffer;
	void* m_nPCMBufferSize;
//	void* m_nPCMBufferSize;
	void* m_pbPCMBuffer;
	BOOL(*CreateAACEnCoder)(AudioTranslateStruct* audioTranslateStruct,int type, int bitspersample, int SampleRate, int channels, int PCM_BITS);
	BOOL(*updateAudioInfo)(AudioTranslateStruct* audioTranslateStruct,uint32_t type, uint32_t audioChannel, uint32_t audioSampleRate, uint32_t audio_framelength, uint32_t sampling_bit);
	void  (*DestroyAACEncoder)(AudioTranslateStruct* audioTranslateStruct);
	void* (*MyDefine_DecoderCreate)(AudioTranslateStruct* audioTranslateStruct,MyDefine_FrameInfo* aInfo);
	void  (*MyDefine_DecoderRelease)(MyDefine_Decoder_Handle aDecoder);
	void  (*MyDefine_EncoderRelease)(MyDefine_Decoder_Handle aDecoder);
}AudioTranslateStruct;

void say_hello() {
	printf("Hello World!\n");
}

void  MyDefine_DecoderRelease(MyDefine_Decoder_Handle aDecoder)
{
	MyDefineDecoder* decoder = (MyDefineDecoder*)aDecoder;

	if (decoder == NULL)
	{
		return;
	}
	if (decoder->VDecoder != NULL)
	{
		avcodec_close(decoder->VDecoder);
		decoder->VDecoder = NULL;
	}
	if (decoder->ADecoder != NULL)
	{
		avcodec_close(decoder->ADecoder);
		decoder->ADecoder = NULL;
	}
	if (decoder->VFrame != NULL)
	{
		av_frame_free(&decoder->VFrame);
		decoder->VFrame = NULL;
	}
	if (decoder->AFrame != NULL)
	{
		av_frame_free(&decoder->AFrame);
		decoder->AFrame = NULL;
	}

	free(decoder);
	decoder = NULL;
}
 void  MyDefine_EncoderRelease(void* aEncoder)
{
	MyDefineEncoder* encoder = (MyDefineEncoder*)aEncoder;

	if (encoder == NULL)
	{
		return;
	}
	if (encoder->VEncoder != NULL)
	{
		avcodec_close(encoder->VEncoder);
		av_free(encoder->VEncoder);
		encoder->VEncoder = NULL;
	}
	if (encoder->AEncoder != NULL)
	{
		avcodec_close(encoder->AEncoder);
		av_free(encoder->AEncoder);
		encoder->AEncoder = NULL;
	}
	if (encoder->VFrame != NULL)
	{
		av_frame_free(&encoder->VFrame);
		encoder->VFrame = NULL;
	}
	if (encoder->AFrame != NULL)
	{
		av_frame_free(&encoder->AFrame);
		encoder->AFrame = NULL;
	}

	free(encoder);
	encoder = NULL;
}

 MyDefine_Decoder_Handle  MyDefine_DecoderCreate(AudioTranslateStruct* AudioTranslateStruct,MyDefine_FrameInfo* aInfo)
{
	if (aInfo->ACodec == MyDefine_CODEC_NONE
		&& aInfo->VCodec == MyDefine_CODEC_NONE)
	{
		return NULL;
	}

	MyDefineDecoder* decoder = (MyDefineDecoder * )malloc(sizeof(MyDefineDecoder));
	if (decoder == NULL)
	{
		return NULL;
	}
	memset(decoder, 0x00, sizeof(MyDefineDecoder));
	// 媒体解码器
	AVCodec* pCodec;
	if (aInfo->VCodec != MyDefine_CODEC_NONE)
	{
		// 请求视频解码器
		pCodec = avcodec_find_decoder(aInfo->VCodec);
		if (pCodec == NULL)
		{
			printf("Could not find video decoder.\n");
			MyDefine_DecoderRelease(decoder);
			return NULL;
		}
		// 申请解码器上下文
		decoder->VDecoder = avcodec_alloc_context3(pCodec);
		if (decoder->VDecoder == NULL)
		{
			printf("Could not alloc video decoder.\n");
			MyDefine_DecoderRelease(decoder);
			return NULL;
		}
		decoder->VDecoder->time_base.num = 1;
		// 帧率
		decoder->VDecoder->time_base.den = aInfo->FramesPerSecond;
		// 每包一个视频帧
		decoder->VDecoder->frame_number = 1;
		// 媒体类型为视频
		decoder->VDecoder->codec_type = AVMEDIA_TYPE_VIDEO;
		decoder->VDecoder->bit_rate = aInfo->VideoBitrate;
		// 视频分辨率
		decoder->VDecoder->width = aInfo->Width;
		decoder->VDecoder->height = aInfo->Height;
		decoder->VDecoder->pix_fmt = AV_PIX_FMT_YUV420P;
		decoder->PixelSize = decoder->VDecoder->width * decoder->VDecoder->height;
		if (avcodec_open2(decoder->VDecoder, pCodec, NULL) < 0)
		{
			printf("Could not open video decoder.\n");
			MyDefine_DecoderRelease(decoder);
			return NULL;
		}

		decoder->VFrame = av_frame_alloc();
		if (decoder->VFrame == NULL)
		{
			printf("Alloc video frame faile!\n");
			MyDefine_DecoderRelease(decoder);
			return NULL;
		}
	}
	if (aInfo->ACodec != MyDefine_CODEC_NONE)
	{
		// 请求音频解码器
		pCodec = avcodec_find_decoder(aInfo->ACodec);
		if (pCodec == NULL)
		{
			printf("Could not find audio decoder.\n");
			MyDefine_DecoderRelease(decoder);
			return NULL;
		}
		// 申请解码器上下文
		decoder->ADecoder = avcodec_alloc_context3(pCodec);
		if (decoder->ADecoder == NULL)
		{
			printf("Could not alloc audio decoder.\n");
			MyDefine_DecoderRelease(decoder);
			return NULL;
		}

		// 参数赋值
		decoder->ADecoder->codec_type = AVMEDIA_TYPE_AUDIO;
		decoder->ADecoder->sample_rate = aInfo->SampleRate;
		decoder->ADecoder->channels = aInfo->Channels;
		//decoder->ADecoder->bit_rate = aInfo->AudioBitrate;
		if ((aInfo->ACodec == MyDefine_CODEC_G726) || (aInfo->ACodec == MyDefine_CODEC_G726LE))
		{
			decoder->ADecoder->bits_per_coded_sample = aInfo->bits_per_coded_sample;
			decoder->ADecoder->sample_fmt = AV_SAMPLE_FMT_S16;
		}
		if (aInfo->ACodec == MyDefine_CODEC_G711A
			|| aInfo->ACodec == MyDefine_CODEC_G711U)
		{
			decoder->ADecoder->sample_fmt = AV_SAMPLE_FMT_S16;
		}
		else
		{
			if (aInfo->Channels == 1)
			{
				decoder->ADecoder->channel_layout = AV_CH_LAYOUT_MONO;
			}
			else
			{
				decoder->ADecoder->channel_layout = AV_CH_LAYOUT_STEREO;
			}
		}
		if (avcodec_open2(decoder->ADecoder, pCodec, NULL) < 0)
		{
			printf("Could not open audio decoder.\n");
			MyDefine_DecoderRelease(decoder);
			return NULL;
		}

		decoder->AFrame = av_frame_alloc();
		if (decoder->AFrame == NULL)
		{
			printf("Alloc audio frame fail!\n");
			MyDefine_DecoderRelease(decoder);
			return NULL;
		}
	}

	return decoder;
}

static int Decode(AVCodecContext* aDecoder, AVPacket* aPacket, AVFrame* aFrame)
{
	int ret;

	ret = avcodec_send_packet(aDecoder, aPacket);
	if (ret < 0)
	{
		printf("Error sending a packet for decoding\n");
		return ret;
	}

	return avcodec_receive_frame(aDecoder, aFrame);
}
 int  MyDefine_DecoderPCM(MyDefine_Decoder_Handle aDecoder, unsigned char* aBytes, int aSize, unsigned char* aPcm)
{
	MyDefineDecoder* decoder = (MyDefineDecoder*)aDecoder;
	if (decoder == NULL || decoder->ADecoder == NULL)
	{
		return 0;
	}
	if (aBytes == NULL || aSize < 1 || aPcm == NULL)
	{
		return 0;
	}

	int ret;
	int out_size = 0;
	AVPacket packet = { 0 };

	packet.data = aBytes;
	packet.size = aSize;

	ret = Decode(decoder->ADecoder, &packet, decoder->AFrame);
	if (ret < 0)
	{
		printf("Decode audio error.\n");
		av_packet_unref(&packet);
		return ret;
	}

	int data_size = av_get_bytes_per_sample(decoder->ADecoder->sample_fmt);

	for (int i = 0; i < decoder->AFrame->nb_samples; i++)
	{
		for (int ch = 0; ch < decoder->ADecoder->channels; ch++)
		{
			memcpy(aPcm, decoder->AFrame->data[ch] + data_size * i, data_size);
			aPcm += data_size;
			out_size += data_size;
		}
	}

	av_packet_unref(&packet);

	return out_size;
}
PcmToAacEncodeInit(PcmToAacStruct* pcmToAacStruct,int SampleRate, int channels, int PCM_BITS)
{
	unsigned int objectType = LOW;
	unsigned int mpegVersion = MPEG2;
	static unsigned int useTns = 0; //#define DEFAULT_TNS     0

	//TODO: config this
	unsigned int nChannels = channels;

	pcmToAacStruct->m_nPCMBitSize = PCM_BITS;
	unsigned long nInputSamples = 0;
	unsigned long nSampleRate = SampleRate;
	unsigned long nMaxOutputBytes = 0;


	/*open FAAC engine*/
	pcmToAacStruct->hEncoder = faacEncOpen(nSampleRate, nChannels, &nInputSamples, &nMaxOutputBytes);
	if (pcmToAacStruct->hEncoder == NULL)
	{
		//if (AAC_DEBUG) 
			printf("%s:[%d] failed to call faacEncOpen !\n", __FUNCTION__, __LINE__);
		//return -1;
		return FALSE;
	}
	pcmToAacStruct->m_nInputSamples = nInputSamples;
	pcmToAacStruct->m_nMaxOutputBytes = nMaxOutputBytes;


	/*get current encoding configuration*/
	pcmToAacStruct->pConfiguration = faacEncGetCurrentConfiguration(pcmToAacStruct->hEncoder);
	pcmToAacStruct->pConfiguration->inputFormat = FAAC_INPUT_16BIT;

	/*0 - raw; 1 - ADTS*/
	pcmToAacStruct->pConfiguration->outputFormat = 1;
	pcmToAacStruct->pConfiguration->useTns = useTns;
	pcmToAacStruct->pConfiguration->aacObjectType = objectType;
	pcmToAacStruct->pConfiguration->mpegVersion = mpegVersion;

	/*set encoding configuretion*/
	faacEncSetConfiguration(pcmToAacStruct->hEncoder, pcmToAacStruct->pConfiguration);

	return TRUE;
}
int PcmToAacEncode(PcmToAacStruct* pcmToAacStruct,int32_t* pbPCMBuffer, unsigned int nPCMBufferSize, unsigned char* pbAACBuffer, unsigned int nMaxOutputBytes)
{
	unsigned int nPCMBitSize = pcmToAacStruct->GetPCMBufferSize(pcmToAacStruct);
	unsigned int nInputSamples = (nPCMBufferSize / (nPCMBitSize / 8));
	int nRet = 0;
	if (AAC_DEBUG) printf("%s:[%d] G711A -> PCM faacEncEncode....\n", __FUNCTION__, __LINE__);
	int nRet = faacEncEncode(pcmToAacStruct->hEncoder, (int*)pbPCMBuffer, nInputSamples, pbAACBuffer, nMaxOutputBytes);
	if (AAC_DEBUG) printf("%s:[%d] G711A -> PCM faacEncEncode\n", __FUNCTION__, __LINE__);
	return nRet;
}

int AudiotoAACStart(AudioTranslateStruct* audioTranslateStruct,unsigned char* inpuf, int inlen, unsigned char* outbuf, int maxlen) {
	int nOutDataLen = 0, AAClen = 0;
	char* szOutData = (char*)_alloca(maxlen * 2);
	AAClen = 0;
	//判断是否有四个字节的海思头//	
	if (inpuf == NULL || inlen < 4)
		return 0;
	if (inpuf[0] == 0 && inpuf[1] == 1 && inpuf[2] == (inlen - 4) / 2 && inpuf[3] == 0)
	{
		nOutDataLen = MyDefine_DecoderPCM(audioTranslateStruct->handle, &inpuf[4], inlen - 4, (unsigned char*)szOutData);
	}
	else
	{
		nOutDataLen = MyDefine_DecoderPCM(audioTranslateStruct->handle, inpuf, inlen, (unsigned char*)szOutData);
	}
	int m_index = 0;
	int m_nPCMBufferSize = 0;
	unsigned char* m_pbPCMBuffer = NULL;
	if (m_index + nOutDataLen <= m_nPCMBufferSize)
	{
		memcpy(m_pbPCMBuffer + m_index, szOutData, nOutDataLen);
		m_index += nOutDataLen;
		if (m_index == m_nPCMBufferSize)
		{
			m_index = 0;
			AAClen = audioTranslateStruct->m_pPCMToAAC->PcmToAacEncode(audioTranslateStruct->m_pPCMToAAC,(int*)m_pbPCMBuffer, m_nPCMBufferSize, outbuf, maxlen);
		}
	}
	else
	{
		int last = m_index + nOutDataLen - m_nPCMBufferSize;//剩下不的部分
		memcpy(m_pbPCMBuffer + m_index, szOutData, m_nPCMBufferSize - m_index);
		AAClen = audioTranslateStruct->m_pPCMToAAC->PcmToAacEncode(audioTranslateStruct,(int*)m_pbPCMBuffer, m_nPCMBufferSize, outbuf, maxlen);
		memcpy(m_pbPCMBuffer, szOutData + m_nPCMBufferSize - m_index, last);
		m_index = last;
	}
	return AAClen;
}
unsigned int GetMaxOutputBytes(PcmToAacStruct pCMtoAACStruct)
{
	return pCMtoAACStruct.m_nMaxOutputBytes;
}
unsigned int GetPCMBufferSize(PcmToAacStruct pCMtoAACStruct)
{
	return (pCMtoAACStruct.m_nInputSamples * (pCMtoAACStruct.m_nPCMBitSize / 8));
}
int FAACAPI faacEncClose(faacEncHandle hEncoder) {
	if (hEncoder != NULL) {
		faacEncClose(hEncoder);
	}
}
BOOL* CreateAACEnCoder(AudioTranslateStruct *audioTranslateStruct,int type, int bitspersample, int SampleRate, int channels, int PCM_BITS)
{
	MyDefine_FrameInfo frame_info;
	memset(&frame_info, 0, sizeof(frame_info));
	switch (type)
	{
	case G711_A:
		frame_info.ACodec = MyDefine_CODEC_G711A;
		break;
	case G711_U:
		frame_info.ACodec = MyDefine_CODEC_G711U;
		break;
	case G726_16KBPS:
		frame_info.ACodec = MyDefine_CODEC_G726LE;
		frame_info.AudioBitrate = 16000;
		break;
	case G726_24KBPS:
		frame_info.ACodec = MyDefine_CODEC_G726LE;
		frame_info.AudioBitrate = 24000;
		break;

	case G726_32KBPS:
		frame_info.ACodec = MyDefine_CODEC_G726LE;
		frame_info.AudioBitrate = 32000;
		break;
	case G726_40KBPS:
		frame_info.ACodec = MyDefine_CODEC_G726LE;
		frame_info.AudioBitrate = 40000;
		break;
	default:
		break;
	}
	frame_info.Channels = channels;
	frame_info.BitsPerSample = PCM_BITS;
	frame_info.bits_per_coded_sample = bitspersample;
	MyDefine_Decoder_Handle handle = audioTranslateStruct->MyDefine_DecoderCreate( audioTranslateStruct,&frame_info);
	audioTranslateStruct->handle = handle;

	
	audioTranslateStruct->m_pPCMToAAC = malloc(sizeof(PcmToAacStruct));
	audioTranslateStruct->m_pPCMToAAC->m_nPCMBitSize = 16;
	audioTranslateStruct->m_pPCMToAAC->Init = &PcmToAacEncodeInit;
	audioTranslateStruct->m_pPCMToAAC->PcmToAacEncode = &PcmToAacEncode;
	audioTranslateStruct->m_pPCMToAAC->Init(audioTranslateStruct->m_pPCMToAAC,SampleRate, channels, PCM_BITS);
	audioTranslateStruct->m_pPCMToAAC->GetMaxOutputBytes = &GetMaxOutputBytes;
	audioTranslateStruct->m_pPCMToAAC->faacEncClose = &faacEncClose;
	audioTranslateStruct->m_pPCMToAAC->Init(SampleRate, channels, PCM_BITS);
	audioTranslateStruct->pbAACBuffer = (unsigned char*)malloc(audioTranslateStruct->m_pPCMToAAC->GetMaxOutputBytes(&audioTranslateStruct)) ;
	audioTranslateStruct->m_nPCMBufferSize = audioTranslateStruct->m_pPCMToAAC->GetPCMBufferSize(&audioTranslateStruct);
	audioTranslateStruct->m_pbPCMBuffer =(unsigned char*) malloc(audioTranslateStruct->m_nPCMBufferSize);
	memset(audioTranslateStruct->m_pbPCMBuffer, 0, audioTranslateStruct->m_nPCMBufferSize);
	return handle;
}
BOOL updateAudioInfo(AudioTranslateStruct* audioTranslateStruct,uint32_t type, uint32_t audioChannel, uint32_t audioSampleRate, uint32_t audio_framelength, uint32_t sampling_bit){
	if (audioTranslateStruct->audioChannel != audioChannel || audioTranslateStruct->audioSampleRate != audioSampleRate || type != audioTranslateStruct->codec_type)
	{
		audioTranslateStruct->audioChannel = audioChannel;
		audioTranslateStruct->audioSampleRate = audioSampleRate;
		audioTranslateStruct->m_samplingBit = sampling_bit;
		audioTranslateStruct->m_audio_frameLength = audio_framelength;
		audioTranslateStruct->codec_type = type;
		return TRUE;
	}
	return TRUE;
}
void DestroyAACEncoder(AudioTranslateStruct* audioTranslateStruct){
	if (audioTranslateStruct->handle != NULL)
	{
		MyDefine_DecoderRelease(audioTranslateStruct->handle);
	}
	if (audioTranslateStruct->m_pPCMToAAC_download != NULL)
	{
		MyDefine_EncoderRelease(audioTranslateStruct->m_pPCMToAAC_download);
	}
	audioTranslateStruct->m_pPCMToAAC->faacEncClose(audioTranslateStruct->m_pPCMToAAC->hEncoder);
	SAFE_DELETE_OBJ(audioTranslateStruct->m_pPCMToAAC);
	//SAFE_DELETE_OBJ(audioTranslateStruct->pbAACBuffer);
	SAFE_DELETE_OBJ(audioTranslateStruct->m_pbPCMBuffer);
	SAFE_DELETE_OBJ(audioTranslateStruct->m_pPCMToAAC_download);
}
AudioBuffer AudiotoAAC(int PayloadType, void* pBuffer, unsigned int bufferLength)
{
	AudioTranslateStruct audioTranslateStruct;
	audioTranslateStruct.audioChannel = 1;
	audioTranslateStruct.audioSampleRate = 8000;
	audioTranslateStruct.m_audio_frameLength = 204;
	audioTranslateStruct.m_samplingBit = 16;
	audioTranslateStruct.CreateAACEnCoder = &CreateAACEnCoder;
	audioTranslateStruct.updateAudioInfo = &updateAudioInfo;
	audioTranslateStruct.DestroyAACEncoder = &DestroyAACEncoder;
	audioTranslateStruct.MyDefine_EncoderRelease = &MyDefine_EncoderRelease;
	audioTranslateStruct.MyDefine_DecoderCreate = &MyDefine_DecoderCreate;
	AudioBuffer buf;
	memset(&buf, '\0', sizeof(AudioBuffer));
	//if (m_pPCMToAAC == NULL) {无用
		int type;
		int bitspersample = 0;
		switch (PayloadType)
		{
		case 6: type = G711_A;      break;
		case 7: type = G711_U;      break;
		case 8:
		{
			//首先判断是不是有海思头？ASF 和RFC格式区别？
			int m_samplingBit = 16;
			bitspersample = (bufferLength - 4) * 8 / 20 / m_samplingBit;
			switch (bitspersample)
			{
			case 2:
				type = G726_16KBPS;
				break;
			case 3:
				type = G726_24KBPS;
				break;
			case 4:
				type = G726_32KBPS;
				break;
			case 5:
				type = G726_40KBPS;
				break;
			default:
				type = G726_40KBPS;
			}

		}
		break; //G726 有几种码流，根据长度和位数获得码流的大小
		case 26:
			type = ADPCM_DVI4; break;
		default:
			printf("Playload type: %d, length: %d.\n", PayloadType, bufferLength);
			return buf;
		}


		printf("length:%d, codec_type:%d\r\n", bufferLength, type);
		printf("Playload type: %d, bitspersample: %d.\n", PayloadType, bitspersample);

		audioTranslateStruct.updateAudioInfo(&audioTranslateStruct,PayloadType, audioTranslateStruct.audioChannel, audioTranslateStruct.audioSampleRate, audioTranslateStruct.m_audio_frameLength, audioTranslateStruct.m_samplingBit);
		audioTranslateStruct.m_type = type;
		audioTranslateStruct.config_m_audio_Rate=8000;
		audioTranslateStruct.config_m_audio_channels=1;
		audioTranslateStruct.CreateAACEnCoder(&audioTranslateStruct,type, bitspersample, audioTranslateStruct.config_m_audio_Rate, audioTranslateStruct.config_m_audio_channels, audioTranslateStruct.m_samplingBit,&audioTranslateStruct);
	//}
	if (audioTranslateStruct.m_pPCMToAAC==NULL) {
		int AAClen = AudiotoAACStart(&audioTranslateStruct,pBuffer, bufferLength , audioTranslateStruct.pbAACBuffer, audioTranslateStruct.m_pPCMToAAC->GetMaxOutputBytes(&audioTranslateStruct));
		if (AAClen > 0) {
			buf.dataPtr = audioTranslateStruct.pbAACBuffer;
			buf.length = AAClen;
			audioTranslateStruct.DestroyAACEncoder(&audioTranslateStruct);
			return buf;
		}
	}
	buf.dataPtr = NULL;
	buf.length = 0;
	audioTranslateStruct.DestroyAACEncoder(&audioTranslateStruct);
	return buf;
}

int main() {
	printf("start");
	const char* TestH264 = "./in_40.g726";
	const char* TestH2642 = "./in_40.AAC";
	int buf_size = 1024 * 512;
	unsigned char* pbuf = (unsigned char*)malloc(buf_size);

	int position = 0;
	FILE*  readFile = fopen(TestH264, "rb");
	if (NULL == readFile)
	{
		printf("Test read file has not found.\n");
		return -1;
	}
	FILE* writeFile = fopen(TestH2642, "rb");
	if (NULL == writeFile)
	{
		printf("Test push file has not found.\n");
		return -1;
	}
	while (1)
	{
		int nReadBytes = fread(pbuf + position, 1, 1, readFile);
		if (nReadBytes < 1)
		{
			if (feof(readFile))
			{
				printf("File read finished.\n");
				break;
			}
			else {
				printf("Read file error!\n");
				break;
			}
		}
	}

	AudioBuffer audioBuffer = AudiotoAAC(8, pbuf, sizeof(pbuf));
	fwrite(audioBuffer.dataPtr, 1, audioBuffer.length, writeFile);
	free(audioBuffer.dataPtr);
	printf("end");
	return 0;
}