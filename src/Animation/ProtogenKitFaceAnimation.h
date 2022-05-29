#pragma once

#include "Animation.h"
#include "KeyFrameTrack.h"
#include "EasyEaseAnimator.h"
#include "..\Objects\SolidCube.h"
#include "..\Morph\NukudeFace.h"
#include "..\Render\Scene.h"
#include "..\Materials\GradientMaterial.h"
#include "..\Materials\SimplexNoise.h"
#include "..\Math\FunctionGenerator.h"
#include "..\Sensors\ButtonHandler.h"
#include "..\Sensors\BoopSensor.h"
#include "..\Materials\NormalMaterial.h"
#include "..\Materials\SpiralMaterial.h"

#include "..\Materials\CombineMaterial.h"
#include "..\Materials\SpectrumAnalyzer.h"


class ProtogenKitFaceAnimation : public Animation{
private:
    float colorMix;

    NukudeFace pM;
    EasyEaseAnimator eEA = EasyEaseAnimator(20, EasyEaseAnimator::Overshoot, 1.0f, 0.35f);
    
    RGBColor noiseSpectrum[4] = {RGBColor(0, 255, 0), RGBColor(255, 0, 0), RGBColor(0, 255, 0), RGBColor(0, 0, 255)};
    GradientMaterial gNoiseMat = GradientMaterial(4, noiseSpectrum, 2.0f, false);
    SimplexNoise sNoise = SimplexNoise(1, &gNoiseMat);
    
    RGBColor gradientSpectrum[2] = {RGBColor(221, 15, 125), RGBColor(214, 35, 168)};
    GradientMaterial gradientMat = GradientMaterial(2, gradientSpectrum, 350.0f, false);
    
    SimpleMaterial redMaterial = SimpleMaterial(RGBColor(255, 0, 0));

    //Spiral Material
    FunctionGenerator fGenMatBend = FunctionGenerator(FunctionGenerator::Sine, 0.8f, 0.9f, 6.7f);
    RGBColor rainbowSpectrum[6] = {RGBColor(255, 0, 0), RGBColor(255, 255, 0), RGBColor(0, 255, 0), RGBColor(0, 255, 255), RGBColor(0, 0, 255), RGBColor(255, 0, 255)};
    SpiralMaterial spiralMaterial = SpiralMaterial(6, rainbowSpectrum, 3.0f, 7.0f);

    //default face material with gradient + simplex noise
    Material* noiseMaterials[2] = {&gradientMat, &sNoise};
    CombineMaterial noiseMaterial = CombineMaterial(CombineMaterial::Lighten, 2, noiseMaterials);

    //for combining angry face with default material
    Material* faceMaterials[2] = {&spiralMaterial, &noiseMaterial};
    CombineMaterial faceMaterial = CombineMaterial(CombineMaterial::Replace, 2, faceMaterials);

    KeyFrameTrack blink = KeyFrameTrack(1, 0.0f, 1.0f, 10, KeyFrameTrack::Cosine);
    KeyFrameTrack mouth = KeyFrameTrack(1, 0.0f, 1.0f, 5, KeyFrameTrack::Cosine);

    FunctionGenerator fGenMatPos = FunctionGenerator(FunctionGenerator::Sine, -10.0f, 10.0f, 4.0f);
    FunctionGenerator fGenRotation = FunctionGenerator(FunctionGenerator::Sine, -30.0f, 30.0f, 2.6f);
    FunctionGenerator fGenScale = FunctionGenerator(FunctionGenerator::Sine, 3.0f, 8.0f, 4.2f);
    FunctionGenerator fGenMatXMove = FunctionGenerator(FunctionGenerator::Sine, -3.5f, 3.5f, 5.3f);
    FunctionGenerator fGenMatYMove = FunctionGenerator(FunctionGenerator::Sine, -3.5f, 3.5f, 6.7f);
    FunctionGenerator fGenMatGradient = FunctionGenerator(FunctionGenerator::Sine, 0.0f, 0.5f, 6.65f);
    
    //Spectrum Analyzer
    SolidCube cube;
    
    GradientMaterial gM = GradientMaterial(6, rainbowSpectrum, 1.0f, false);
    SpectrumAnalyzer sA = SpectrumAnalyzer(22, Vector2D(250, 200), Vector2D(160, 130), &gM, true, true);

    Material* spectrumMaterials[2] = {&sA, &sNoise};
    CombineMaterial spectrumMaterial = CombineMaterial(CombineMaterial::Lighten, 2, spectrumMaterials);

    BoopSensor boop;
    float simplexNoiseDepth = 0.0f;
    bool talk = true;

    void LinkEasyEase(){
        eEA.AddParameter(pM.GetMorphWeightReference(NukudeFace::Anger), NukudeFace::Anger, 30, 0.0f, 1.0f);
        eEA.AddParameter(pM.GetMorphWeightReference(NukudeFace::Sadness), NukudeFace::Sadness, 30, 0.0f, 1.0f);
        eEA.AddParameter(pM.GetMorphWeightReference(NukudeFace::Surprised), NukudeFace::Surprised, 30, 0.0f, 1.0f);
        eEA.AddParameter(pM.GetMorphWeightReference(NukudeFace::Doubt), NukudeFace::Doubt, 30, 0.0f, 1.0f);
        eEA.AddParameter(pM.GetMorphWeightReference(NukudeFace::Frown), NukudeFace::Frown, 30, 0.0f, 1.0f);
        eEA.AddParameter(pM.GetMorphWeightReference(NukudeFace::LookUp), NukudeFace::LookUp, 30, 0.0f, 1.0f);
        eEA.AddParameter(pM.GetMorphWeightReference(NukudeFace::LookDown), NukudeFace::LookDown, 30, 0.0f, 1.0f);

        eEA.AddParameter(pM.GetMorphWeightReference(NukudeFace::vrc_v_ou), NukudeFace::vrc_v_ou, 5, 0.0f, 1.0f);
        eEA.AddParameter(pM.GetMorphWeightReference(NukudeFace::vrc_v_ee), NukudeFace::vrc_v_ee, 30, 0.0f, 1.0f);
        eEA.AddParameter(pM.GetMorphWeightReference(NukudeFace::vrc_v_ff), NukudeFace::vrc_v_ff, 30, 0.0f, 1.0f);
        eEA.AddParameter(pM.GetMorphWeightReference(NukudeFace::vrc_v_aa), NukudeFace::vrc_v_aa, 5, 0.0f, 1.0f);
        eEA.AddParameter(pM.GetMorphWeightReference(NukudeFace::vrc_v_nn), NukudeFace::vrc_v_nn, 30, 0.0f, 1.0f);
        eEA.AddParameter(pM.GetMorphWeightReference(NukudeFace::vrc_v_dd), NukudeFace::vrc_v_dd, 30, 0.0f, 1.0f);
        eEA.AddParameter(pM.GetMorphWeightReference(NukudeFace::vrc_v_ih), NukudeFace::vrc_v_ih, 30, 0.0f, 1.0f);
        eEA.AddParameter(pM.GetMorphWeightReference(NukudeFace::vrc_v_pp), NukudeFace::vrc_v_pp, 30, 0.0f, 1.0f);
        
        eEA.AddParameter(pM.GetMorphWeightReference(NukudeFace::HideBlush), NukudeFace::HideBlush, 20, 1.0f, 0.0f);
        
        eEA.AddParameter(&colorMix, 99, 40, 0.0f, 1.0f);
    }

    void LinkParameters(){
        blink.AddParameter(pM.GetMorphWeightReference(NukudeFace::Blink));
        mouth.AddParameter(pM.GetMorphWeightReference(NukudeFace::vrc_v_kk));
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

    void AddMouthKeyFrames(){
        mouth.AddKeyFrame(0.0f, 0.0f);
        mouth.AddKeyFrame(1.5f, 1.0f);
        mouth.AddKeyFrame(4.0f, 0.0f);
    }

    void ChangeInterpolationMethods(){
        eEA.SetInterpolationMethod(NukudeFace::HideBlush, EasyEaseAnimator::Cosine);
        eEA.SetInterpolationMethod(NukudeFace::Sadness, EasyEaseAnimator::Cosine);
        eEA.SetInterpolationMethod(NukudeFace::vrc_v_ou, EasyEaseAnimator::Cosine);
        eEA.SetInterpolationMethod(99, EasyEaseAnimator::Cosine);

        eEA.SetConstants(NukudeFace::vrc_v_aa, 1.0f, 0.5f);
        eEA.SetConstants(NukudeFace::vrc_v_ou, 0.9f, 0.45f);
    }

public:
    ProtogenKitFaceAnimation() : Animation(2) {
        scene->AddObject(pM.GetObject());
        scene->AddObject(cube.GetObject());

        LinkEasyEase();
        LinkParameters();

        AddBlinkKeyFrames();
        AddMouthKeyFrames();

        ChangeInterpolationMethods();

        pM.GetObject()->SetMaterial(&faceMaterial);
        cube.GetObject()->SetMaterial(&spectrumMaterial);
        noiseMaterial.SetFirstLayerOpacity(0.6f);
        spectrumMaterial.SetFirstLayerOpacity(1.0f);

        ButtonHandler::Initialize(0, 6);//8 is number of faces
        boop.Initialize(5);
    }

    void UpdateKeyFrameTracks(){
        blink.Update();
        mouth.Update();
    }

    void Default(){
        pM.GetObject()->Enable();
        cube.GetObject()->Disable();
        
        pM.Reset();
        blink.Play();
        mouth.Play();

        eEA.AddParameterFrame(99, 0.0f);

        talk = true;
    }

    void Angry(){
        pM.GetObject()->Enable();
        cube.GetObject()->Disable();
        
        pM.Reset();
        blink.Play();
        mouth.Play();

        eEA.AddParameterFrame(NukudeFace::Anger, 1.0f);
        eEA.AddParameterFrame(NukudeFace::vrc_v_ee, 1.0f);

        talk = true;
    }

    void Sad(){
        pM.GetObject()->Enable();
        cube.GetObject()->Disable();
        
        pM.Reset();
        blink.Play();
        mouth.Play();

        eEA.AddParameterFrame(NukudeFace::Sadness, 1.0f);
        eEA.AddParameterFrame(NukudeFace::Frown, 1.0f);

        talk = true;
    }

    void Surprised(){
        pM.GetObject()->Enable();
        cube.GetObject()->Disable();
        
        pM.Reset();
        blink.Play();
        mouth.Play();

        eEA.AddParameterFrame(NukudeFace::Surprised, 1.0f);
        eEA.AddParameterFrame(NukudeFace::vrc_v_aa, 1.0f);
        eEA.AddParameterFrame(NukudeFace::HideBlush, 0.0f);
        eEA.AddParameterFrame(99, 0.5f);

        talk = true;
    }
    
    void Doubt(){
        pM.GetObject()->Enable();
        cube.GetObject()->Disable();
        
        pM.Reset();
        blink.Play();
        mouth.Play();

        eEA.AddParameterFrame(NukudeFace::Doubt, 1.0f);
        eEA.AddParameterFrame(NukudeFace::vrc_v_nn, 1.0f);

        talk = true;
    }
    
    void Frown(){
        pM.GetObject()->Enable();
        cube.GetObject()->Disable();
        
        pM.Reset();
        blink.Play();
        mouth.Play();

        eEA.AddParameterFrame(NukudeFace::Frown, 1.0f);
        eEA.AddParameterFrame(NukudeFace::vrc_v_dd, 1.0f);

        talk = true;
    }

    void LookUp(){
        pM.GetObject()->Enable();
        cube.GetObject()->Disable();
        
        pM.Reset();
        blink.Play();
        mouth.Play();

        eEA.AddParameterFrame(NukudeFace::LookUp, 1.0f);
        eEA.AddParameterFrame(NukudeFace::vrc_v_ih, 1.0f);

        talk = true;
    }

    void LookDown(){
        pM.GetObject()->Enable();
        cube.GetObject()->Disable();

        pM.Reset();
        blink.Play();
        mouth.Play();

        eEA.AddParameterFrame(NukudeFace::LookDown, 1.0f);
        eEA.AddParameterFrame(NukudeFace::vrc_v_pp, 1.0f);

        talk = true;
    }

    void SpectrumAnalyzerFace(){
        pM.GetObject()->Disable();
        cube.GetObject()->Enable();
    }

    void FadeIn(float stepRatio) override {}
    void FadeOut(float stepRatio) override {}

    Object3D* GetObject(){
        return pM.GetObject();
    }

    float offset = 0.0f;

    void Update(float ratio) override {
        bool isBooped = boop.isBooped();
        float mouthMove = 0.0f;
        uint8_t mode = ButtonHandler::GetValue();//change by button press

        sA.Update();
        sA.SetHueAngle(ratio * 360.0f * 4.0f);

        mouthMove = sA.GetCurrentValue();

        //Serial.println(mouthMove);

        if (isBooped){
            Surprised();
        }
        else{
            if (mode == 0) Default();
            else if (mode == 1) Angry();
            else if (mode == 2) Doubt();
            else if (mode == 3) Frown();
            else if (mode == 4) LookUp();
            else if (mode == 5) Sad();
            else SpectrumAnalyzerFace();
        }

        pM.SetMorphWeight(NukudeFace::BiggerNose, 1.0f);
        pM.SetMorphWeight(NukudeFace::MoveEye, 1.0f);

        UpdateKeyFrameTracks();

        if(talk) {
            eEA.AddParameterFrame(NukudeFace::vrc_v_aa, mouthMove);
            eEA.AddParameterFrame(NukudeFace::vrc_v_ou, mouthMove);
        }

        eEA.Update();
        pM.Update();

        //Serial.print(eEA.GetValue(NukudeFace::vrc_v_ou));
        //Serial.print('\t');
        //Serial.print(mouthMove);
        //Serial.println('\t');
        
        float x = fGenMatXMove.Update();
        float y = fGenMatYMove.Update();
        
        float sweep = fGenMatGradient.Update();
        float sShift = sweep * 0.004f + 0.005f;

        simplexNoiseDepth += 0.1f;

        gNoiseMat.SetGradientPeriod(0.5f + sweep * 6.0f);
        gNoiseMat.HueShift(ratio * 360 * 2);
        sNoise.SetScale(Vector3D(sShift, sShift, sShift));
        sNoise.SetZPosition(simplexNoiseDepth);
        
        spiralMaterial.SetBend(fGenMatBend.Update());
        spiralMaterial.SetRotationAngle((1.0f - ratio) * 360.0f);
        spiralMaterial.SetPositionOffset(Vector2D(0.0f, 75.0f));
        
        faceMaterial.SetFirstLayerOpacity(colorMix);
        
        pM.GetObject()->GetTransform()->SetRotation(Vector3D(0.0f, 0.0f, 0.0f));
        pM.GetObject()->GetTransform()->SetPosition(Vector3D(170.0f + x, 10.0f + y, 600.0f));
        pM.GetObject()->GetTransform()->SetScale(Vector3D(-1.0f, 0.625f, 0.7f));

        pM.GetObject()->UpdateTransform();
        
        cube.GetObject()->ResetVertices();
        cube.GetObject()->GetTransform()->SetPosition(Vector3D(1000, 1000, 10000.0f));
        cube.GetObject()->GetTransform()->SetScale(Vector3D(1000, 1000, 1));
        cube.GetObject()->UpdateTransform();
    }
};