#pragma once

#include "Animation.h"
#include "KeyFrameTrack.h"
#include "EasyEaseAnimator.h"
#include "..\Morph\ProtoDRMorph.h"
#include "..\Render\Scene.h"
#include "..\Materials\GradientMaterial.h"
#include "..\Materials\SimplexNoise.h"
#include "..\Math\FunctionGenerator.h"
#include "..\Sensors\SerialSync.h"
#include "..\Sensors\ButtonHandler.h"
#include "..\Materials\NormalMaterial.h"

#include "..\Objects\Spyro.h"

#include "Flash\ImageSequences\Rainbow.h"

class ProtoDRMorphAnimation : public Animation{
private:
    ProtoDR pM;
    EasyEaseAnimator eEA = EasyEaseAnimator(11, EasyEaseAnimator::Cosine);

    RGBColor spectrum[4] = {RGBColor(0, 255, 0), RGBColor(255, 0, 0), RGBColor(0, 255, 0), RGBColor(0, 0, 255)};
    GradientMaterial gNoiseMat = GradientMaterial(4, spectrum, 2.0f, false);
    SimplexNoise sNoise = SimplexNoise(1, &gNoiseMat);

    NormalMaterial normalMaterial;
    
    FunctionGenerator fGenMatPos = FunctionGenerator(FunctionGenerator::Sine, -10.0f, 10.0f, 4.0f);
    RainbowSequence gif = RainbowSequence(Vector2D(200, 145), Vector2D(100, 70), 15);

    KeyFrameTrack blink = KeyFrameTrack(1, 0.0f, 1.0f, 10, KeyFrameTrack::Cosine);
    KeyFrameTrack topFinOuter = KeyFrameTrack(1, 0.0f, 1.0f, 5, KeyFrameTrack::Cosine);
    KeyFrameTrack topFinInner = KeyFrameTrack(1, 0.0f, 1.0f, 5, KeyFrameTrack::Cosine);
    KeyFrameTrack topFinGap = KeyFrameTrack(1, 0.0f, 1.0f, 5, KeyFrameTrack::Cosine);
    KeyFrameTrack midFin = KeyFrameTrack(3, 0.0f, 1.0f, 5, KeyFrameTrack::Cosine);
    KeyFrameTrack botFinLR1 = KeyFrameTrack(1, 0.0f, 1.0f, 10, KeyFrameTrack::Cosine);
    KeyFrameTrack botFinLR2 = KeyFrameTrack(1, 0.0f, 1.0f, 10, KeyFrameTrack::Cosine);
    KeyFrameTrack botFinLR3 = KeyFrameTrack(1, 0.0f, 1.0f, 10, KeyFrameTrack::Cosine);
    KeyFrameTrack botFinLR4 = KeyFrameTrack(1, 0.0f, 1.0f, 10, KeyFrameTrack::Cosine);
    KeyFrameTrack botFinLR5 = KeyFrameTrack(1, 0.0f, 1.0f, 10, KeyFrameTrack::Cosine);
    KeyFrameTrack mouth = KeyFrameTrack(1, 0.0f, 1.0f, 5, KeyFrameTrack::Cosine);

    Spyro spyro;
    FunctionGenerator fGenRotation = FunctionGenerator(FunctionGenerator::Sine, -30.0f, 30.0f, 2.6f);
    FunctionGenerator fGenScale = FunctionGenerator(FunctionGenerator::Sine, 3.0f, 8.0f, 4.2f);

    void LinkEasyEase(){
        eEA.AddParameter(pM.GetMorphWeightReference(ProtoDR::BlushEye), ProtoDR::BlushEye, 40, 0.0f);
        eEA.AddParameter(pM.GetMorphWeightReference(ProtoDR::HideBlush), ProtoDR::HideBlush, 1, 1.0f);
        eEA.AddParameter(pM.GetMorphWeightReference(ProtoDR::HideEyeBrow), ProtoDR::HideEyeBrow, 1, 0.0f);
        eEA.AddParameter(pM.GetMorphWeightReference(ProtoDR::OwOMouth), ProtoDR::OwOMouth, 60, 0.0f);

        eEA.AddParameter(pM.GetMorphWeightReference(ProtoDR::SadEye), ProtoDR::SadEye, 70, 0.0f);
        eEA.AddParameter(pM.GetMorphWeightReference(ProtoDR::SadEyeBrow), ProtoDR::SadEyeBrow, 80, 0.0f);
        eEA.AddParameter(pM.GetMorphWeightReference(ProtoDR::SadMouth), ProtoDR::SadMouth, 90, 0.0f);

        eEA.AddParameter(pM.GetMorphWeightReference(ProtoDR::FlatMouth), ProtoDR::FlatMouth, 50, 0.0f);
        eEA.AddParameter(pM.GetMorphWeightReference(ProtoDR::DeadEye), ProtoDR::DeadEye, 1, 0.0f);

        eEA.AddParameter(pM.GetMorphWeightReference(ProtoDR::HeartEye), ProtoDR::HeartEye, 30, 0.0f);

        eEA.AddParameter(pM.GetMorphWeightReference(ProtoDR::OwO), ProtoDR::OwO, 90, 0.0f);
    }

    void LinkParameters(){
        blink.AddParameter(pM.GetMorphWeightReference(ProtoDR::ClosedEye));

        topFinOuter.AddParameter(pM.GetMorphWeightReference(ProtoDR::TopFinOuterThin));
        topFinInner.AddParameter(pM.GetMorphWeightReference(ProtoDR::TopFinInnerThin));
        topFinGap.AddParameter(pM.GetMorphWeightReference(ProtoDR::TopFinInnerCloseGap));

        midFin.AddParameter(pM.GetMorphWeightReference(ProtoDR::MidFinBotThin));
        midFin.AddParameter(pM.GetMorphWeightReference(ProtoDR::MidFinMidBigger));
        midFin.AddParameter(pM.GetMorphWeightReference(ProtoDR::MidFinTopThin));

        botFinLR1.AddParameter(pM.GetMorphWeightReference(ProtoDR::BotFinLR1Thin));
        botFinLR2.AddParameter(pM.GetMorphWeightReference(ProtoDR::BotFinLR2Thin));
        botFinLR3.AddParameter(pM.GetMorphWeightReference(ProtoDR::BotFinLR3Thin));
        botFinLR4.AddParameter(pM.GetMorphWeightReference(ProtoDR::BotFinLR4Thin));
        botFinLR5.AddParameter(pM.GetMorphWeightReference(ProtoDR::BotFinLR5Thin));

        mouth.AddParameter(pM.GetMorphWeightReference(ProtoDR::ShockedMouth));
    }

    void AddBlinkKeyFrames(){
        blink.AddKeyFrame(0.0f, 0.0f);
        blink.AddKeyFrame(2.75f, 0.0f);
        blink.AddKeyFrame(3.0f, 1.0f);
        blink.AddKeyFrame(3.25f, 0.0f);
        blink.AddKeyFrame(9.75f, 0.0f);
        blink.AddKeyFrame(10.0f, 1.0f);
        blink.AddKeyFrame(10.25f, 0.0f);
        blink.AddKeyFrame(10.75f, 0.0f);
        blink.AddKeyFrame(11.0f, 1.0f);
        blink.AddKeyFrame(11.25f, 0.0f);
        blink.AddKeyFrame(15.0f, 0.0f);
    }

    void AddTopFinKeyFrames(){
        topFinOuter.AddKeyFrame(0.0f, 0.0f);
        topFinOuter.AddKeyFrame(1.5f, 1.0f);
        topFinOuter.AddKeyFrame(3.0f, 0.0f);

        topFinInner.AddKeyFrame(0.0f, 0.0f);
        topFinInner.AddKeyFrame(0.5f, 0.0f);
        topFinInner.AddKeyFrame(1.5f, 1.0f);
        topFinInner.AddKeyFrame(2.5f, 0.0f);
        topFinInner.AddKeyFrame(3.0f, 0.0f);

        topFinGap.AddKeyFrame(0.0f, 0.0f);
        topFinGap.AddKeyFrame(1.0f, 0.0f);
        topFinGap.AddKeyFrame(1.5f, 1.0f);
        topFinGap.AddKeyFrame(2.0f, 0.0f);
        topFinGap.AddKeyFrame(3.0f, 0.0f);
    }

    void AddMidFinKeyFrames(){
        midFin.AddKeyFrame(0.0f, 0.0f);
        midFin.AddKeyFrame(2.5f, 1.0f);
        midFin.AddKeyFrame(5.0f, 0.0f);
    }

    void AddBotFinKeyFrames(){
        botFinLR1.AddKeyFrame(0.0f, 0.0f);
        botFinLR2.AddKeyFrame(0.0f, 0.0f);
        botFinLR3.AddKeyFrame(0.0f, 0.0f);
        botFinLR4.AddKeyFrame(0.0f, 0.0f);
        botFinLR5.AddKeyFrame(0.0f, 1.0f);

        botFinLR1.AddKeyFrame(0.25f, 1.0f);
        botFinLR2.AddKeyFrame(0.25f, 0.0f);
        botFinLR3.AddKeyFrame(0.25f, 0.0f);
        botFinLR4.AddKeyFrame(0.25f, 0.0f);
        botFinLR5.AddKeyFrame(0.25f, 0.0f);

        botFinLR1.AddKeyFrame(0.5f, 0.0f);
        botFinLR2.AddKeyFrame(0.5f, 1.0f);
        botFinLR3.AddKeyFrame(0.5f, 0.0f);
        botFinLR4.AddKeyFrame(0.5f, 0.0f);
        botFinLR5.AddKeyFrame(0.5f, 0.0f);

        botFinLR1.AddKeyFrame(0.75f, 0.0f);
        botFinLR2.AddKeyFrame(0.75f, 0.0f);
        botFinLR3.AddKeyFrame(0.75f, 1.0f);
        botFinLR4.AddKeyFrame(0.75f, 0.0f);
        botFinLR5.AddKeyFrame(0.75f, 0.0f);

        botFinLR1.AddKeyFrame(1.0f, 0.0f);
        botFinLR2.AddKeyFrame(1.0f, 0.0f);
        botFinLR3.AddKeyFrame(1.0f, 0.0f);
        botFinLR4.AddKeyFrame(1.0f, 1.0f);
        botFinLR5.AddKeyFrame(1.0f, 0.0f);
        
        botFinLR1.AddKeyFrame(1.25f, 0.0f);
        botFinLR2.AddKeyFrame(1.25f, 0.0f);
        botFinLR3.AddKeyFrame(1.25f, 0.0f);
        botFinLR4.AddKeyFrame(1.25f, 0.0f);
        botFinLR5.AddKeyFrame(1.25f, 1.0f);
    }

    void AddMouthKeyFrames(){
        mouth.AddKeyFrame(0.0f, 0.0f);
        mouth.AddKeyFrame(1.5f, 1.0f);
        mouth.AddKeyFrame(4.0f, 0.0f);
    }

public:
    ProtoDRMorphAnimation() : Animation(2) {
        scene->AddObject(pM.GetObject());
        scene->AddObject(spyro.GetObject());

        LinkEasyEase();
        LinkParameters();

        AddBlinkKeyFrames();
        AddTopFinKeyFrames();
        AddMidFinKeyFrames();
        AddBotFinKeyFrames();
        AddMouthKeyFrames();

        pM.GetObject()->SetMaterial(&gif);

        SerialSync::Initialize();
        ButtonHandler::Initialize(15, 8);
    }

    void UpdateKeyFrameTracks(){
        blink.Update();
        topFinOuter.Update();
        topFinInner.Update();
        topFinGap.Update();
        midFin.Update();
        botFinLR1.Update();
        botFinLR2.Update();
        botFinLR3.Update();
        botFinLR4.Update();
        botFinLR5.Update();
        mouth.Update();
    }

    void Default(){
        pM.Reset();
        blink.Play();
        mouth.Play();
    }

    void OwO(){
        pM.Reset();
        blink.Pause();
        blink.Reset();
        mouth.Pause();
        mouth.Reset();

        eEA.AddParameterFrame(ProtoDR::BlushEye, 1.0f);
        eEA.AddParameterFrame(ProtoDR::HideBlush, 0.0f);
        eEA.AddParameterFrame(ProtoDR::HideEyeBrow, 1.0f);
        eEA.AddParameterFrame(ProtoDR::OwOMouth, 1.0f);
    }

    void Sad(){
        pM.Reset();
        blink.Play();
        mouth.Pause();
        mouth.Reset();

        eEA.AddParameterFrame(ProtoDR::SadEye, 1.0f);
        eEA.AddParameterFrame(ProtoDR::SadEyeBrow, 1.0f);
        eEA.AddParameterFrame(ProtoDR::SadMouth, 1.0f);
    }

    void Dead(){
        pM.Reset();
        blink.Pause();
        blink.Reset();
        mouth.Pause();
        mouth.Reset();

        eEA.AddParameterFrame(ProtoDR::FlatMouth, 1.0f);
        eEA.AddParameterFrame(ProtoDR::DeadEye, 1.0f);
        eEA.AddParameterFrame(ProtoDR::HideEyeBrow, 1.0f);
    }

    void Heart(){
        pM.Reset();
        blink.Pause();
        blink.Reset();
        mouth.Pause();
        mouth.Reset();

        eEA.AddParameterFrame(ProtoDR::HeartEye, 1.0f);
        eEA.AddParameterFrame(ProtoDR::HideEyeBrow, 1.0f);
        eEA.AddParameterFrame(ProtoDR::OwOMouth, 1.0f);
    }

    void OwO2(){
        pM.Reset();
        blink.Pause();
        blink.Reset();
        mouth.Pause();
        mouth.Reset();
        
        topFinOuter.Reset();
        topFinInner.Reset();
        topFinGap.Reset();
        midFin.Reset();
        botFinLR1.Reset();
        botFinLR2.Reset();
        botFinLR3.Reset();
        botFinLR4.Reset();
        botFinLR5.Reset();
        
        pM.SetMorphWeight(ProtoDR::HideBlush, 0.0f);
        pM.SetMorphWeight(ProtoDR::HideSecondEye, 0.0f);

        eEA.AddParameterFrame(ProtoDR::OwO, 1.0f);
    }

    void SpyroDisplay(float ratio, bool normal){
        pM.GetObject()->Disable();
        spyro.GetObject()->Enable();

        float x = fGenRotation.Update();
        float sx = fGenScale.Update();
        
        Quaternion rotation = Rotation(EulerAngles(Vector3D(x, ratio * 720.0f, 0), EulerConstants::EulerOrderXZYS)).GetQuaternion();

        spyro.GetObject()->ResetVertices();

        spyro.GetObject()->GetTransform()->SetRotation(rotation);
        spyro.GetObject()->GetTransform()->SetScale(Vector3D(sx, sx, sx));
        spyro.GetObject()->GetTransform()->SetPosition(Vector3D(0.0f, 30.0f, 600.0f));

        spyro.GetObject()->UpdateTransform();

        if(!normal){
            spyro.GetObject()->SetMaterial(&spyro.material);
        }
        else{
            spyro.GetObject()->SetMaterial(&normalMaterial);
        }
    }

    void FadeIn(float stepRatio) override {}
    void FadeOut(float stepRatio) override {}

    Object3D* GetObject(){
        return pM.GetObject();
    }

    float offset = 0.0f;

    void Update(float ratio) override {
        pM.GetObject()->Enable();//Due to Spyro track
        spyro.GetObject()->Disable();

        /*
        uint8_t mode = ButtonHandler::GetValue();
        SerialSync::SetMode(mode);
        SerialSync::SetRatio(ratio);
        SerialSync::Send();
        */
        
        SerialSync::Read();

        //update offset only 2% of the time
        if(SerialSync::GetRatio() < 0.02f){
            if(ratio > SerialSync::GetRatio()) offset = ratio - 1.0f - SerialSync::GetRatio();
            else offset = ratio - SerialSync::GetRatio();
        }

        //adjust current frame sync to new esp32
        ratio = fmod(ratio - offset, 1.0f);//override input to synchronize from esp

        uint8_t mode = SerialSync::GetMode();

        Serial.print(mode);
        Serial.print('\t');
        Serial.println(ratio);

        if (mode == 0) Heart();
        else if (mode == 1) OwO();
        else if (mode == 2) Sad();
        else if (mode == 3) Dead();
        else if (mode == 4) SpyroDisplay(ratio, false);
        else if (mode == 5) SpyroDisplay(ratio, true);
        else if (mode == 6) Default();
        else OwO2();

        UpdateKeyFrameTracks();
        eEA.Update();
        pM.Update();
        
        float x = sinf(ratio * 3.14159f / 180.0f * 360.0f * 2.0f) * 3.0f;
        float y = cosf(ratio * 3.14159f / 180.0f * 360.0f * 3.0f) * 3.0f;
        
        float linSweep = ratio > 0.5f ? 1.0f - ratio : ratio;
        float sShift = linSweep * 0.002f + 0.005f;

        gNoiseMat.SetGradientPeriod(0.5f + linSweep * 6.0f);
        gNoiseMat.HueShift(ratio * 360 * 2);
        sNoise.SetScale(Vector3D(sShift, sShift, sShift));
        sNoise.SetZPosition(x * 4.0f);

        float shift = fGenMatPos.Update();

        gif.SetPosition(Vector2D(20.0f + shift, 135.0f + shift));
        gif.SetSize(Vector2D(-440, 350));
        gif.SetRotation(15.0f);
        gif.Update();
        
        pM.GetObject()->GetTransform()->SetRotation(Vector3D(0, 180.0f, 0.0f));
        pM.GetObject()->GetTransform()->SetPosition(Vector3D(x, y, 600.0f));
        pM.GetObject()->GetTransform()->Scale(Vector3D(1.0f, 1.0f, 1.0f));

        pM.GetObject()->UpdateTransform();
    }
};