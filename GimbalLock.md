# Gimbal Lock in This Project

## 요약

이 프로젝트는 짐벌락을 **내부 회전 상태를 quaternion으로 유지하는 방식**으로 회피한다.

- `FRotator`는 입력과 표시용 인터페이스다.
- 실제 회전 저장은 `FTransform` 내부의 `FQuat Rotation`이 담당한다.
- 회전 누적과 회전 합성은 quaternion 곱으로 처리한다.
- 특이점 처리는 quaternion 연산을 위한 것이 아니라, quaternion을 다시 Euler로 표시할 때 값이 튀지 않게 하기 위한 처리다.

## 짐벌락이 왜 생기는가

짐벌락은 회전을 `Pitch`, `Yaw`, `Roll` 같은 Euler 각도로 표현하고, 그 값을 축별로 계속 누적할 때 발생한다.

대표적으로 pitch가 `+90` 또는 `-90`도 근처에 가면 두 회전축이 거의 겹친다. 이 상태에서는 원래 서로 독립적이어야 할 회전 자유도 하나가 사라진 것처럼 보인다. 결과적으로:

- 특정 축 회전이 다른 축 회전과 구분되지 않거나
- 회전 방향이 갑자기 이상하게 바뀌거나
- 사용자가 기대하지 않은 축으로 회전이 말려 들어갈 수 있다.

## 이 프로젝트의 해결 방식

이 프로젝트는 `FRotator`를 내부 상태로 직접 누적하지 않는다.

대신:

1. 사용자가 Euler 값을 입력할 수는 있다.
2. 그 값은 바로 quaternion으로 변환된다.
3. 내부 회전 상태는 `FQuat`로 저장된다.
4. 이후 회전 누적은 quaternion 곱으로만 처리된다.

즉 중요한 것은 **입력 형식이 Euler인지 아닌지**가 아니라, **내부 상태와 누적 방식이 quaternion인지**다.

### 내부 저장 구조

`FTransform`은 회전을 `FRotator`가 아니라 `FQuat`로 보관한다.

- `Engine/Source/Math/Transform.h`
- `Engine/Source/Math/Transform.cpp`

따라서 transform 합성, world/local 회전 처리, gizmo 드래그 결과 적용은 모두 quaternion 기준으로 작동한다.

### 회전 누적 방식

회전은 `Pitch += ...`, `Yaw += ...`, `Roll += ...`처럼 누적하지 않는다.

대신:

- 현재 회전 상태 `CurrentRotation`
- 이번 입력으로부터 만든 delta quaternion `DeltaRotation`

을 이용해:

`CurrentRotation = CurrentRotation * DeltaRotation`

처럼 합성한다.

이 방식은 Euler 축이 겹치는 문제를 내부 연산에서 피할 수 있다.

## Gizmo에서도 같은 원칙을 사용한다

에디터 회전 gizmo도 같은 방식이다.

드래그가 시작되면:

- 시작 시점의 오브젝트 회전을 quaternion으로 저장한다.

드래그 중에는:

- 마우스 이동으로부터 signed angle을 계산하고
- 그 각도와 축으로 delta quaternion을 만든 뒤
- 시작 quaternion에 곱해서 새 회전을 만든다.

즉 gizmo 조작 중에도 Euler 각도를 직접 누적하지 않는다.

관련 코드는 다음 위치에 있다.

- `Editor/Source/Gizmo/Gizmo.cpp`

## 특이점 처리는 무엇을 위한 것인가

여기서 중요한 점은, **특이점 처리는 짐벌락을 막기 위한 주된 장치가 아니라는 것**이다.

짐벌락 회피 자체는 이미 quaternion 기반 내부 상태로 해결되어 있다.

특이점 처리는 quaternion을 다시 `Pitch / Yaw / Roll`로 보여줄 때 필요하다.

왜냐하면 quaternion은 하나의 회전을 안정적으로 표현할 수 있지만, 이를 Euler로 바꾸는 순간 특정 자세에서는 표현이 유일하지 않기 때문이다. 같은 회전을 여러 Euler 조합으로 표현할 수 있어서 값이 갑자기 튀어 보일 수 있다.

이 프로젝트는 `FQuat -> FRotator` 변환에서:

- 먼저 안전하게 pitch를 복원하고
- `cos(pitch)`가 거의 0이면 특이점으로 판단한 뒤
- 안정적인 대체 공식으로 yaw를 계산하고
- roll은 대표값으로 고정한다

는 방식으로 UI용 Euler 값을 안정화한다.

즉:

- 내부 회전 상태는 그대로 quaternion으로 유지된다.
- 표현 단계에서만 Euler 값을 일관되게 하나 선택한다.

## 정리

이 프로젝트의 결론은 다음과 같다.

1. 짐벌락은 Euler 회전을 내부 상태로 누적할 때 생긴다.
2. 이 프로젝트는 내부 회전 상태를 quaternion으로 유지해 짐벌락을 회피한다.
3. `FRotator`는 입력과 표시용 인터페이스로만 사용한다.
4. 특이점 처리는 quaternion을 다시 Euler로 표시할 때 값이 튀지 않게 하기 위한 UI/표현 계층의 처리다.

## 발표용 한 문장

“저희는 짐벌락을 Euler 회전을 계속 누적하는 방식으로 처리하지 않고, 내부 회전 상태를 quaternion으로 유지하고 quaternion 곱으로 회전을 합성해서 회피했습니다. 그리고 사용자에게는 여전히 Euler 각도로 보여줘야 하기 때문에, quaternion을 Euler로 변환할 때 특이점 구간에서는 안정적인 대표값을 고르는 별도 처리를 넣었습니다.”
