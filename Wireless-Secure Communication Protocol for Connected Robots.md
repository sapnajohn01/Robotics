Assignment 5: Secure Communication Protocol for Connected Robots

Architecture overview and threat context\
•	Scope: Robot, controller app, and optional gateway, connected viAuthentication and session management\
Mechanism\
•	Pre-shared secret: A device-bound token stored in secure flash or OTP region.\
•	Challenge–response: Robot issues a random nonce; controller returns HMAC over nonce using pre-shared key. Robot verifies before opening a command session.\
•	Rate limiting: Reject after N failed attempts; enforce backoff and lockout.\
Minimal microcontroller-friendly flow\
1.	HELLO: Controller requests session.\
2.	CHAL: Robot sends 16–32 byte random nonce.\
3.	AUTH: Controller sends HMAC_SHA256(nonce, PSK) and a device ID.\
4.	OK/ERR: Robot validates; on OK, issues short-lived session token.
c
// Pseudocode (C-like, MCU friendly)\
bool authenticate(uint8_t *nonce, uint8_t *hmac_in, const uint8_t *psk) {\
  uint8_t hmac_calc[32];\
  hmac_sha256(nonce, NONCE_LEN, psk, PSK_LEN, hmac_calc);\
  return timing_safe_equals(hmac_calc, hmac_in, 32);
}

void on_auth_attempt(AuthMsg msg) {\
  if (failed_count >= MAX_FAILS) { alert("lockout"); return; }\
  if (!authenticate(msg.nonce, msg.hmac, PSK)) {\
    failed_count++; log_evt("auth_fail", msg.device_id);\
    if (failed_count % FAIL_ALERT_THRESH == 0) alert("multiple_auth_fail");
    return;
  }
  failed_count = 0;\
  session_token = make_session_token(); // random + expiry\
  log_evt("auth_success", msg.device_id);\
}

Encryption of sensitive data\
Options suitable for MCUs\
•	AES-CTR or AES-GCM (preferred): Use a vetted lightweight AES library; CTR is simple and fast; GCM adds integrity. Ensure unique IV per session and per message.\
•	XOR (only for demos): Extremely weak; use solely for non-sensitive test traffic to illustrate encryption plumbing. Do not ship.
c
// AES-CTR example (conceptual)\
void encrypt_msg(uint8_t *plaintext, size_t len,\
                 uint8_t *key, uint8_t *iv, uint8_t *ciphertext) {\
  aes_ctr(plaintext, len, key, AES_KEY_LEN, iv, ciphertext);
}

void send_secured(Command cmd) {\
  uint8_t iv[12]; random_bytes(iv, 12);\
  uint8_t buf[CMD_MAX]; size_t n = serialize(cmd, buf);\
  uint8_t ct[CMD_MAX];\
  encrypt_msg(buf, n, session_key, iv, ct);\
  tx_packet(iv, 12, ct, n);\
}
•	Keying: Derive a per-session key via HKDF from the PSK and nonce: session_key = HKDF(PSK, nonce).\
•	Integrity: If GCM not available, append HMAC over ciphertext and header.\
•	Healthcare note: Even minimal robots may carry identifiers or status telemetry considered sensitive; encryption at the application layer mitigates confidentiality risks when links are shared or proxied. Protocol choice and network stack impact how you wrap encryption if transport security is absent or weak\

a Bluetooth LE or Wi Fi.\
•	Principles: Minimal attack surface, explicit trust boundaries, fail-secure defaults, auditable events.\
•	Threats addressed: Unauthorized command injection, eavesdropping, replay, escalation of privileges, brute force login. In healthcare contexts, continuous sharing of sensitive data mandates confidentiality and integrity; even simple systems must enforce those guarantees to protect patient privacy. As robots increasingly integrate with IoT/ICS ecosystems, their communication surfaces become attractive attack vectors, demanding protocol hardening and monitoring. Choice of protocol and link characteristics (BLE, MQTT/TCP, custom serial) influence latency, reliability, and your security wrapping strategy

