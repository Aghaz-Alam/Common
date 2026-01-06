What “Traceability” refers to
Traceability links related items across stages, for example:
Requirement → Design → Code → Test case → Defect
Raw material → Supplier → Batch → Product → Customer
Change request → Impacted modules → Tests → Release




What “Triaging” means in this context
Triaging answers three key questions:
How serious is this? (severity/impact)
How urgent is this? (priority/timeline)
What should be done? (fix, defer, reject, escalate)




What is being triaged?
In a traceability context, you usually triage:
❌ Missing links (requirement not linked to test case)
⚠️ Broken links (test exists but requirement changed)
🔁 Conflicting mappings (one test linked to wrong requirement)
🆕 New or changed requirements
🐞 Defects not traced back to requirements
🚫 Obsolete artifacts still linked




Why triaging is important in traceability
Triaging helps to:
Maintain end-to-end traceability
Avoid coverage gaps
Control scope creep
Support impact analysis
Meet audit / compliance needs (ISO, CMMI, DO-178C, etc.)