In Jenkins (especially when integrated with Gerrit), GVS most commonly means:
✅ GVS = Gerrit Verified Status
GVS refers to the verification result that Jenkins sends back to Gerrit after running CI jobs.






What is GVS in Simple Terms?
GVS is the “Verified” vote/label in Gerrit that Jenkins sets automatically based on build & test results.
✔ Build/Test PASS → Verified +1
❌ Build/Test FAIL → Verified -1
This status controls whether a change can be merged.







Where GVS Fits (Gerrit + Jenkins Flow)
Developer pushes code
   ↓
Gerrit creates change
   ↓
Jenkins triggered
   ↓
Jenkins runs build & tests
   ↓
Jenkins sets GVS in Gerrit
   ↓
Merge allowed or blocked








Example in Gerrit UI
You will see something like:
Code-Review +2
Verified +1   ← (This is GVS)

Or on failure:
Verified -1
❌ Build failed in Jenkins job: adas-active-safety-ci
📌 That “Verified” label = GVS






Why GVS Is Critical in ADAS Projects
GVS ensures:
❌ No untested code is merged
✔ Mandatory automated verification
✔ ASPICE SWE.4 / SWE.5 compliance
✔ ISO 26262 verification evidence
✔ Enforced quality gates

Without GVS +1, merge is blocked, even if:
Code review is approved
Senior engineer reviewed it





What Jenkins Checks Before Setting GVS
Typical ADAS Jenkins pipeline:
Build (AUTOSAR SWCs / perception / controls)
Unit tests (gTest)
Static analysis (MISRA / cppcheck)
Coverage threshold
Packaging
Only if all pass → GVS = +1







GVS vs Code-Review (Important Distinction)
| Label              | Set By         | Meaning              |
| ------------------ | -------------- | -------------------- |
| **Code-Review**    | Human reviewer | Code quality & logic |
| **Verified (GVS)** | Jenkins        | Build & test result  |


Note: GVS in Jenkins refers to the Gerrit Verified Status that Jenkins sets after running CI jobs, 
indicating whether a code change has passed automated build and test verification.




Q: Can code merge without GVS +1?
👉 ❌ No, in a gated Gerrit workflow, merge is blocked.

Q: Who sets GVS?
👉 Jenkins (via Gerrit Trigger / SSH).